#include <engine/actors/base_actor.h>

BaseActor::BaseActor() {
    this->renderedX = 0;
    this->renderedY = 0;
    this->renderedZ = 0;

    this->renderedScaleX = 1;
    this->renderedScaleY = 1;
    this->renderedScaleZ = 1;

    this->renderedRotation = 0.0f;
    this->renderedVisible = true;

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

    this->rotation = 0.0f;

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

float BaseActor::getWidth() {
    return this->renderedWidth;
}

float BaseActor::getHeight() {
    return this->renderedHeight;
}

ActorRenderType BaseActor::getActorRenderType() {
    return this->actorRenderType;
}

void BaseActor::update(float dT) {}

void BaseActor::render() {}

void BaseActor::calculateRenderedPosition() {
    BaseActor* objectParent = this->parent;

    this->renderedWidth = this->width * this->getScaleX();
    this->renderedHeight = this->height * this->getScaleY();

    if (objectParent != nullptr) {
        if (this->relativePosMode) {
            this->renderedX = objectParent->getWidth() * objectParent->getX();
            this->renderedY = objectParent->getHeight() * objectParent->getY();
        } else {
            this->renderedX = objectParent->getX();
            this->renderedY = objectParent->getY();
        }
        
        this->renderedZ = objectParent->getZ();

        this->renderedScaleX = objectParent->getScaleX();
        this->renderedScaleY = objectParent->getScaleY();
        this->renderedScaleZ = objectParent->getScaleZ();

        this->renderedRotation = objectParent->getRotation();

        this->renderedVisible = objectParent->getVisible();
    } else {
        this->renderedVisible = true;
    }

    this->renderedX += this->x + this->pivotX;
    this->renderedY += this->y + this->pivotY;
    this->renderedZ += this->z + this->pivotZ;

    this->renderedScaleX *= this->scaleX;
    this->renderedScaleY *= this->scaleY;
    this->renderedScaleZ *= this->scaleZ;

    this->renderedRotation += this->rotation;

    this->renderedVisible = this->renderedVisible && this->visible;
}