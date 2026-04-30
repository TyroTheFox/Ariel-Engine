#include <engine/actors/base_actor.h>

BaseActor::BaseActor() {
    this->renderedX = 0;
    this->renderedY = 0;
    this->renderedZ = 0;

    this->renderedScaleX = 1;
    this->renderedScaleY = 1;
    this->renderedScaleZ = 1;

    this->x = 0;
    this->y = 0;
    this->z = 0;
    
    this->pivotX = 0;
    this->pivotY = 0;
    this->pivotZ = 0;

    this->scaleX = 1;
    this->scaleY = 1;
    this->scaleZ = 1;

    this->anchorX = 0.5;
    this->anchorY = 0.5;
    this->anchorZ = 0.5;

    this->rotation = 0;

    this->visible = true;

    this->parent = nullptr;
}

BaseActor::~BaseActor() {}

float BaseActor::getX() {
    return this->renderedX;
}

float BaseActor::getY() {
    return this->renderedY;
}

float BaseActor::getZ() {
    return this->renderedZ;
}

float BaseActor::getScaleX() {
    return this->renderedScaleX;
}

float BaseActor::getScaleY() {
    return this->renderedScaleY;
}

float BaseActor::getScaleZ() {
    return this->renderedScaleZ;
}

float BaseActor::getAnchorX() {
    return this->anchorX;
}

float BaseActor::getAnchorY() {
    return this->anchorY;
}

float BaseActor::getAnchorZ() {
    return this->anchorZ;
}

float BaseActor::getRotation() {
    return this->renderedRotation;
}

bool BaseActor::getVisible() {
    return this->renderedVisible;
}

void BaseActor::update(float dT) {}

void BaseActor::render() {}

void BaseActor::calculateRenderedPosition() {
    BaseActor* objectParent = this->parent;

    if (objectParent != nullptr) {
        renderedX = objectParent->getX();
        renderedY = objectParent->getY();
        renderedZ = objectParent->getZ();

        renderedScaleX = objectParent->getScaleX();
        renderedScaleY = objectParent->getScaleY();
        renderedScaleZ = objectParent->getScaleZ();

        renderedRotation = objectParent->getRotation();

        renderedVisible = objectParent->getRotation();
    }

    renderedX += this->x + this->pivotX;
    renderedY += this->y + this->pivotY;
    renderedZ += this->z + this->pivotZ;

    renderedScaleX *= this->scaleX;
    renderedScaleY *= this->scaleY;
    renderedScaleZ *= this->scaleZ;

    renderedRotation += this->rotation;

    renderedVisible = renderedVisible && this->visible;
}