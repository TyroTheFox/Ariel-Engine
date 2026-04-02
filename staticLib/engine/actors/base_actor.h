#pragma once

#include <string>

#include "sling.h"

class BaseActor {
    protected:
        float renderedX = 0;
        float renderedY = 0;

        float renderedScaleX = 0;
        float renderedScaleY = 0;
    public:
        std::string id;
        float x = 0;
        float y = 0;
        float pivotX = 0;
        float pivotY = 0;

        float scaleX = 0;
        float scaleY = 0;

        float rotation = 0;

        bool visible = true;

        BaseActor* parent = nullptr;

        float getX();
        float getY();

        virtual void update();
        virtual void render();

        void calculateRenderedPosition();
};

float BaseActor::getX() {
    return this->renderedX;
}

float BaseActor::getY() {
    return this->renderedY;
}

void BaseActor::calculateRenderedPosition() {
    BaseActor* parent = this->parent;

    if (parent != nullptr) {
        renderedX = parent->getX();
        renderedY = parent->getY();
    }

    renderedX += this->x + this->pivotX;
    renderedY += this->y + this->pivotY;
}