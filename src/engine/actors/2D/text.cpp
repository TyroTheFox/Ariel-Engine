#include "engine/actors/2D/text.h"

Text::Text(std::string id) {
    raylib::Font defaultFont = ::GetFontDefault();
    this->id = id;
    this->setDefaults(&defaultFont);
}

Text::Text(std::string id, raylib::Font* fontPtr) {
    this->id = id;
    this->setDefaults(fontPtr);
}

Text::~Text() {
}

void Text::setDefaults(raylib::Font* fontPtr) {
    this->actorRenderType = ACTOR_2D;

    this->wordWrap = false;
    this->bounds = raylib::Rectangle(25.0f, 25.0f, 250.0f, 250.0f);
    this->fontSize = 20.0f;
    this->spacing = 2.0f;

    this->raylibText = raylib::Text(*fontPtr, "", this->fontSize, this->spacing, BLACK);
}

void Text::setFont(raylib::Font* fontPtr) {
    this->raylibText.SetFont(*fontPtr);
}

void Text::setText(std::string text) {
    this->raylibText.SetText(text);
}

void Text::setWordWrap(bool wordWrap) {
    this->wordWrap = wordWrap;
}

void Text::setWordWrapBounds(raylib::Rectangle rect) {
    this->bounds = rect;
}

void Text::setColour(raylib::Color colour) {
    this->raylibText.SetColor(colour);
}

void Text::setSpacing(float spacing) {
    this->spacing = spacing;
    this->raylibText.SetSpacing(this->spacing);
}

void Text::update(float dT) {}

void Text::render() {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    if (this->wordWrap) {
        this->drawTextWithWordWrap();
    } else {
        this->raylibText.Draw(
            raylib::Vector2(this->getX(), this->getY()), 
            this->getRotation(), 
            raylib::Vector2(this->raylibText.MeasureEx().x * this->getAnchorX(), this->raylibText.MeasureEx().y * this->getAnchorY())
        );
    }
}

// Draw text using font inside rectangle limits with support for text selection
void Text::drawTextWithWordWrap() {
    int length = ::TextLength(this->raylibText.text.c_str());  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)this->raylibText.font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = ::GetCodepoint(&this->raylibText.GetText().c_str()[i], &codepointByteCount);
        int index = ::GetGlyphIndex(this->raylibText.font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (this->raylibText.font.glyphs[index].advanceX == 0) ? this->raylibText.font.recs[index].width*scaleFactor : this->raylibText.font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + this->spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container)
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > this->bounds.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (this->raylibText.font.baseSize + (float)this->raylibText.font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > this->bounds.width))
                {
                    textOffsetY += (this->raylibText.font.baseSize + (float)this->raylibText.font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + this->raylibText.font.baseSize*scaleFactor) > this->bounds.height) break;

                // // Draw selection background
                // bool isGlyphSelected = false;
                // if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                // {
                //     DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                //     isGlyphSelected = true;
                // }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    ::DrawTextCodepoint(this->raylibText.font, codepoint, (Vector2){ this->bounds.x + textOffsetX, this->bounds.y + textOffsetY }, fontSize, this->raylibText.color);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (this->raylibText.font.baseSize + (float)this->raylibText.font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                // selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}