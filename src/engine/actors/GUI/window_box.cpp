#include <engine/actors/GUI/window_box.h>

WindowBox::WindowBox(std::string id) {
    this->id = id;
    this->actorType = "Window Box";
    this->setDefaults();
}

WindowBox::~WindowBox() {
}

void WindowBox::setDefaults() {
    this->actorRenderType = ACTOR_2D;
}

void WindowBox::update(float dT) {
    this->renderedWidth = this->width * this->getScaleX();
    this->renderedHeight = this->height * this->getScaleY();
}

void WindowBox::render() {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    GuiWindowBox((Rectangle) {
            this->getX(), 
            this->getY(), 
            this->renderedWidth, 
            this->renderedHeight
        },
        this->id.c_str()
    );
}
