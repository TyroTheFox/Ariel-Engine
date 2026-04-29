#include "engine/actors/2D/animated_sprite.h"

AnimatedSprite::AnimatedSprite(std::string id, TextureAtlas* textureAtlas, std::string defaultFrame) {
    this->id = id;
    this->textureAtlas = textureAtlas;

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeed = 24;
    this->frameSpeedCount = 0;

    this->currentAnimation = "";

    this->playing = false;
    this->defaultFrameID = defaultFrame;
}

AnimatedSprite::~AnimatedSprite() {
}

void AnimatedSprite::setTextureAtlas(TextureAtlas* textureAtlas) {
    this->textureAtlas = textureAtlas;
}

void AnimatedSprite::playAnimation(std::string animationID) {
    this->playing = true;
    this->currentAnimation = animationID;

    std::vector<std::string> animationFrames = this->textureAtlas->getAnimationFrames(this->currentAnimation);

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
        this->currentFrameID = this->defaultFrameID;
        return;
    }

    this->frameSpeedCount++;

    if (this->frameSpeedCount >= 60/this->frameSpeed) {
        this->currentFrameIndex++;
        this->frameSpeedCount = 0;

        std::vector<std::string> animationFrames = this->textureAtlas->getAnimationFrames(this->currentAnimation);

        if (this->currentFrameIndex >= animationFrames.size() - 1) {
            if (this->loopCount == 0) {
                this->stopAnimation();
                return;
            } else if (this->loopCount > 0) {
                this->loopCount--;                
            }

            this->currentFrameIndex = 0;
        }

        this->currentFrameID = animationFrames.at(this->currentFrameIndex);

    }
}

void AnimatedSprite::render() {
    if (!this->visible) {
        return;
    }

    raylib::Texture2D* atlasTexture = this->textureAtlas->getAtlasTexture();

    this->calculateRenderedPosition();

    if (atlasTexture->IsValid() && this->currentFrameID != "") {
        raylib::Rectangle frameRect = this->textureAtlas->getFrameRect(this->currentFrameID);
        atlasTexture->Draw(frameRect, { this->getX(), this->getY() }, raylib::Color::White());
    }
}
