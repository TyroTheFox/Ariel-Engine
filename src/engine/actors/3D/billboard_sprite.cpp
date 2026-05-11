#include "engine/actors/3D/billboard_sprite.h"

BillboardSprite::BillboardSprite(std::string id, TextureAtlas* textureAtlas, std::string defaultAnimation) {
    this->actorRenderType = ACTOR_3D;
    
    this->id = id;
    this->textureAtlas = textureAtlas;

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeedCount = 0;

    this->currentAnimation = nullptr;

    this->playing = false;
    this->defaultAnimationID = defaultAnimation;
    this->loopCount = -1;

    this->origin = raylib::Vector2(0.5f, 0.5f);

    this->camera3D = new raylib::Camera3D();
}

BillboardSprite::~BillboardSprite() {
}

void BillboardSprite::setTextureAtlas(TextureAtlas* textureAtlas) {
    this->textureAtlas = textureAtlas;
}

void BillboardSprite::setSceneCamera(raylib::Camera3D* camera) {
    this->camera3D = camera;
}

void BillboardSprite::playAnimation(std::string animationID) {
    this->playing = true;
    SpriteAnimation* spriteAnimation = this->textureAtlas->getAnimation(animationID);
    this->currentAnimation = spriteAnimation;

    std::vector<std::string> animationFrames = spriteAnimation->frames;

    this->currentFrameID = animationFrames.at(0);
    this->frameSpeedCount = 0;
    this->loopCount = spriteAnimation->loopCount;

    this->animationStarted.emit(animationID);
}

void BillboardSprite::stopAnimation() {
    this->animationStopped.emit(this->currentAnimation->id);

    this->playing = false;
    this->currentAnimation = nullptr;

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeedCount = 0;
    this->loopCount = -1;
}

void BillboardSprite::update(float dT) {
    if (!this->playing) {
        this->currentFrameID = this->defaultAnimationID;
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

void BillboardSprite::render() {
    if (!this->getVisible()) {
        return;
    }

    raylib::Texture2D* atlasTexture = this->textureAtlas->getAtlasTexture();

    this->calculateRenderedPosition();

    if (atlasTexture->IsValid() && this->currentFrameID != "") {
        raylib::Rectangle frameRect = this->textureAtlas->getFrameRect(this->currentFrameID);
        bool isFrameRotated = this->textureAtlas->getFrameRotated(this->currentFrameID);

        raylib::Vector2 calculatedScale{0.0f, 0.0f};
        float xRotatedFrameOffset = 0;

        if (isFrameRotated) {
            calculatedScale = raylib::Vector2(this->getScaleX(), (frameRect.height/frameRect.width) * this->getScaleY());
            xRotatedFrameOffset = (frameRect.width * ((frameRect.height/frameRect.width) * this->getScaleY()) * 0.5);
        } else {
            calculatedScale = raylib::Vector2((frameRect.width/frameRect.height) * this->getScaleX(), this->getScaleY());
        }

        atlasTexture->DrawBillboard(
            *this->camera3D, 
            frameRect, 
            raylib::Vector3(this->getX() - xRotatedFrameOffset, this->getY(), this->getZ()), 
            raylib::Vector3(0.0f, 1.0f, 0.0f), 
            calculatedScale,
            raylib::Vector2(0.5f, 0.5f),
            this->getRotation() + (isFrameRotated ? 90 : 0),
            raylib::Color::White()
        );
    }
}