#include <engine/actors/base_actor.h>

BaseActor::BaseActor() {
    this->renderedX = 0;
    this->renderedY = 0;
    this->renderedZ = 0;

    this->renderedScaleX = 0;
    this->renderedScaleY = 0;
    this->renderedScaleZ = 0;

    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->pivotX = 0;
    this->pivotY = 0;
    this->pivotZ = 0;

    this->scaleX = 0;
    this->scaleY = 0;
    this->scaleZ = 0;

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

void BaseActor::update(float dT) {}

void BaseActor::render() {}

void BaseActor::calculateRenderedPosition() {
    BaseActor* objectParent = this->parent;

    if (objectParent != nullptr) {
        renderedX = objectParent->getX();
        renderedY = objectParent->getY();
        renderedZ = objectParent->getZ();
    }

    renderedX += this->x + this->pivotX;
    renderedY += this->y + this->pivotY;
    renderedZ += this->z + this->pivotZ;
}