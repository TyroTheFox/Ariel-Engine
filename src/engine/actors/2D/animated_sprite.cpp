#include "engine/actors/2D/animated_sprite.h"

AnimatedSprite::AnimatedSprite(std::string id, raylib::Texture2D* atlasTexture) {
    this->id = id;
    this->texture = atlasTexture;

    this->frameMap = std::map<std::string, raylib::Rectangle>{};
    this->animationMap = std::map<std::string, std::vector<std::string>>{};

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeed = 24;
    this->frameSpeedCount = 0;

    this->currentAnimation = "";

    this->playing = false;
}

AnimatedSprite::~AnimatedSprite() {
}

void AnimatedSprite::setTexture(raylib::Texture2D* texturePtr) {
    this->texture = texturePtr;
}

void AnimatedSprite::setFrame(std::string frameName) {
    if (this->frameMap.size() > 0) {
        this->currentFrameID = frameName;
    }
}

void AnimatedSprite::addFrame(std::string frameID, raylib::Rectangle frameRect) {
    this->frameMap.insert({frameID, frameRect});
}

void AnimatedSprite::addAnimation(std::string animationId, std::vector<std::string> animationFrames) {
    this->animationMap.insert({animationId, animationFrames});
}

void AnimatedSprite::playAnimation(std::string animationID) {
    this->playing = true;
    this->currentAnimation = animationID;

    std::vector<std::string> animationFrames = this->animationMap.at(this->currentAnimation);

    this->currentFrameID = animationFrames.at(0);
    this->frameSpeedCount = 0;
}

void AnimatedSprite::setFrameSpeed(int speed) {
    this->frameSpeed = speed;
}

void AnimatedSprite::setLoopCount(int loop) {
    this->loopCount = loop;
}

void AnimatedSprite::stopAnimation() {
    this->playing = false;
    this->currentAnimation = "";

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeedCount = 0;
}

void AnimatedSprite::update(float dT) {
    if (!this->playing) {
        return;
    }

    this->frameSpeedCount += dT;

    if (this->frameSpeedCount >= 60/this->frameSpeed) {
        this->currentFrameIndex++;
        this->frameSpeedCount = 0;

        std::vector<std::string> animationFrames = this->animationMap.at(this->currentAnimation);

        if (this->currentFrameIndex >= animationFrames.size() - 1) {
            this->currentFrameID = animationFrames.at(this->currentFrameIndex);

            if (this->loopCount == 0) {
                this->stopAnimation();
                return;
            } else if (this->loopCount > 0) {
                this->loopCount--;                
            }

            this->currentFrameIndex = 0;
        }

    }
}

void AnimatedSprite::render() {
    if (!this->visible) {
        return;
    }

    this->calculateRenderedPosition();

    if (this->texture->IsValid() && this->currentFrameID != "" && this->frameMap.size() > 0) {
        raylib::Rectangle frameRect = this->frameMap.at(this->currentFrameID);
        this->texture->Draw(frameRect, { this->getX(), this->getY() }, raylib::Color::White());
    }
}
