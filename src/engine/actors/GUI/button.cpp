#include <engine/actors/GUI/button.h>

Button::Button(std::string id) {
    this->id = id;
    this->actorType = "Button";
    this->setDefaults();
}

Button::~Button() {
}

void Button::setDefaults() {
    this->actorRenderType = ACTOR_2D;

    this->fontSize = 20.0f;
    this->padding = 10;
}

void Button::setText(std::string text)
{
    this->text = text;
}

void Button::connectActorSlot(sl::Slot<>* slot) {
    this->button_pushed.connect(slot);
}

void Button::update(float dT)
{
    if (this->pushed) {
        this->button_pushed.emit();
        this->pushed = false;
    }
}

void Button::render() {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    Vector2 textSize = MeasureTextEx(GuiGetFont(), this->text.c_str(), (float)GuiGetStyle(DEFAULT, TEXT_SIZE), (float)GuiGetStyle(DEFAULT, TEXT_SPACING));
    
    int lineCount = 0;
    this->GetTextLines(this->text.c_str(), &lineCount); // Only using the line count

    if (GuiButton(
        (Rectangle) {
            this->getX() + this->padding, 
            this->getY() + (textSize.y * this->getScaleY()), 
            this->getScaleX() + this->padding * textSize.x, 
            textSize.y * lineCount
        },
        this->text.c_str()
    )) {
        this->pushed = true;
    }
}

const char **Button::GetTextLines(const char *text, int *count)
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
