#include <engine/actors/GUI/label.h>

Label::Label(std::string id) {
    
}

Label::~Label() {
}

void Label::setDefaults(raylib::Font* fontPtr) {
    this->actorRenderType = ACTOR_2D;

    this->fontSize = 20.0f;
}

void Label::update(float dT) {

}

void Label::render() {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    GuiLabel(
        (Rectangle) {
            this->getX(), 
            this->getY() + (this->getScaleY() * this->fontSize), 
            this->getScaleX() * this->fontSize, 
            fontSize
        }, 
        this->text.c_str()
    );
}