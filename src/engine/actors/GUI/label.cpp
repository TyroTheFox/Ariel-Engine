#include <engine/actors/GUI/label.h>

Label::Label(std::string id) {
    this->id = id;
    this->actorType = "Text";
    this->setDefaults();
}

Label::~Label() {
}

void Label::setDefaults() {
    this->actorRenderType = ACTOR_2D;

    this->fontSize = 20.0f;
    this->padding = 10;
}

void Label::setText(std::string text)
{
    this->text = text;
}

void Label::update(float dT)
{
}

void Label::render() {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    Vector2 textSize = MeasureTextEx(GuiGetFont(), this->text.c_str(), (float)GuiGetStyle(DEFAULT, TEXT_SIZE), (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
    
    int lineCount = 0;
    this->GetTextLines(this->text.c_str(), &lineCount); // Only using the line count

    GuiLabel(
        (Rectangle) {
            this->getX() + this->padding, 
            this->getY() + (textSize.y * this->getScaleY()), 
            this->getScaleX() + this->padding * textSize.x, 
            textSize.y * lineCount
        }, 
        this->text.c_str()
    );
}

const char **Label::GetTextLines(const char *text, int *count)
{
    #define RAYGUI_MAX_TEXT_LINES   128

    static const char *lines[RAYGUI_MAX_TEXT_LINES] = { 0 };
    for (int i = 0; i < RAYGUI_MAX_TEXT_LINES; i++) lines[i] = NULL;    // Init NULL pointers to substrings

    int textLength = (int)strlen(text);

    lines[0] = text;
    *count = 1;

    for (int i = 0; (i < textLength) && (*count < RAYGUI_MAX_TEXT_LINES); i++)
    {
        if ((text[i] == '\n') && ((i + 1) < textLength))
        {
            lines[*count] = &text[i + 1];
            *count += 1;
        }
    }

    return lines;
}
