#include "engine/actors/2D/animated_sprite.h"

AnimatedSprite::AnimatedSprite(std::string id, TextureAtlas* textureAtlas, std::string defaultFrame) {
    this->actorRenderType = ACTOR_2D;
    
    this->id = id;
    this->textureAtlas = textureAtlas;

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeedCount = 0;

    this->currentAnimation = nullptr;

    this->playing = false;
    this->defaultFrameID = defaultFrame;
    this->loopCount = -1;
}

AnimatedSprite::~AnimatedSprite() {
}

void AnimatedSprite::setTextureAtlas(TextureAtlas* textureAtlas) {
    this->textureAtlas = textureAtlas;
}

void AnimatedSprite::playAnimation(std::string animationID) {
    this->playing = true;
    SpriteAnimation* spriteAnimation = this->textureAtlas->getAnimation(animationID);
    this->currentAnimation = spriteAnimation;

    std::vector<std::string> animationFrames = spriteAnimation->frames;

    this->currentFrameID = animationFrames.at(0);
    this->frameSpeedCount = 0;
    this->loopCount = spriteAnimation->loopCount;

    this->animationStarted.emit(animationID);
}

void AnimatedSprite::stopAnimation() {
    this->animationStopped.emit(this->currentAnimation->id);

    this->playing = false;
    this->currentAnimation = nullptr;

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeedCount = 0;
    this->loopCount = -1;
}

void AnimatedSprite::update(float dT) {
    if (!this->playing) {
        this->currentFrameID = this->defaultFrameID;
        return;
    }

    this->frameSpeedCount++;

    this->animationUpdating.emit(this->currentAnimation->id, this->currentFrameIndex, dT);

    if (this->frameSpeedCount >= 60/this->currentAnimation->playSpeed) {
        this->currentFrameIndex++;
        this->frameSpeedCount = 0;

        std::vector<std::string> animationFrames = this->currentAnimation->frames;

        if (this->currentFrameIndex >= animationFrames.size() - 1) {
            if (this->loopCount == 0) {
                this->stopAnimation();
                return;
            } else if (this->loopCount > 0) {
                this->loopCount--;                
            }

            this->animationLooped.emit(this->currentAnimation->id, this->loopCount);

            this->currentFrameIndex = 0;
        }

        this->currentFrameID = animationFrames.at(this->currentFrameIndex);
    }
}

void AnimatedSprite::render() {
    if (!this->getVisible()) {
        return;
    }

    raylib::Texture2D* atlasTexture = this->textureAtlas->getAtlasTexture();

    this->calculateRenderedPosition();

    if (atlasTexture->IsValid() && this->currentFrameID != "") {
        raylib::Rectangle frameRect = this->textureAtlas->getFrameRect(this->currentFrameID);
        float invertedTextureScale = 1 / this->textureAtlas->getTextureScale();

        raylib::Vector2 calculatedScale = raylib::Vector2(
            frameRect.GetWidth() * this->getScaleX() * invertedTextureScale, 
            frameRect.GetHeight() * this->getScaleY() * invertedTextureScale
        );

        raylib::Rectangle destinationRect = raylib::Rectangle(
            this->getX(), this->getY(), 
            calculatedScale.x, calculatedScale.y
        );

        atlasTexture->Draw(
            frameRect, destinationRect, 
            { calculatedScale.x * this->getAnchorX(), calculatedScale.y * this->getAnchorY() }, 
            this->getRotation(), 
            raylib::Color::White()
        );
    }
}
