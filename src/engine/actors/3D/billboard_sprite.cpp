#include "engine/actors/3D/billboard_sprite.h"

BillboardSprite::BillboardSprite(std::string id, TextureAtlas* textureAtlas, std::string defaultAnimation) {
    this->actorRenderType = ACTOR_3D_BILLBOARD;
    
    this->id = id;
    this->actorType = "BillboardSprite";
    this->textureAtlas_Deffuse = textureAtlas;
    this->textureAtlas_Normal = textureAtlas;
    this->textureAtlas_Occlusion = textureAtlas;
    this->textureAtlas_Specular = textureAtlas;

    this->currentFrameID = "";
    this->currentFrameIndex = -1;
    this->frameSpeedCount = 0;

    this->currentAnimation = nullptr;

    this->playing = false;
    this->defaultAnimationID = defaultAnimation;
    this->loopCount = -1;

    this->origin = raylib::Vector2(0.5f, 0.5f);

    this->camera3D = new raylib::Camera3D();

    ShaderManager shaderManager = ShaderManager();
    this->deferredShader = shaderManager.getShaderPtr("deferred");
    this->gBufferShader = shaderManager.getShaderPtr("gbuffer");

    // this->tilingVector = Vector2();
    // this->tilingVector.x = 0.5;
    // this->tilingVector.y = 0.5;
    
    // this->metallicValueLoc = this->gBufferShader->getShaderLocation("metallicValue");
    // this->roughnessValueLoc = this->gBufferShader->getShaderLocation("roughnessValue");
    // this->aoValueLoc = this->gBufferShader->getShaderLocation("aoValue");
    // this->emissiveIntensityLoc = this->gBufferShader->getShaderLocation("emissivePower");
    // this->emissiveColorLoc = this->gBufferShader->getShaderLocation("emissiveColor");
    // this->textureTilingLoc = this->gBufferShader->getShaderLocation("tiling");

    // // Set old car metallic and roughness values
    // this->gBufferShader->setShaderValue(metallicValueLoc, &this->metalness, SHADER_UNIFORM_FLOAT);
    // this->gBufferShader->setShaderValue(roughnessValueLoc, &this->roughness, SHADER_UNIFORM_FLOAT);
    // this->gBufferShader->setShaderValue(aoValueLoc, &this->occlusion, SHADER_UNIFORM_FLOAT);

    //     // Set old car model texture tiling, emissive color and emissive intensity parameters on shader
    // this->gBufferShader->setShaderValue(textureTilingLoc, &this->tilingVector, SHADER_UNIFORM_VEC2);

    // Vector4 emissiveColor = ColorNormalize(raylib::Color::White());
    // this->gBufferShader->setShaderValue(emissiveColorLoc, &emissiveColor, SHADER_UNIFORM_VEC4);

    // this->gBufferShader->setShaderValue(emissiveIntensityLoc, &this->emissiveIntensity, SHADER_UNIFORM_FLOAT);
}

BillboardSprite::~BillboardSprite() {
    delete this->textureAtlas_Deffuse;
    delete this->textureAtlas_Normal;
    delete this->textureAtlas_Occlusion;
    delete this->textureAtlas_Specular;

    delete this->currentAnimation;
    delete this->camera3D;
}

void BillboardSprite::setDeffuseTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Deffuse = new TextureAtlas(this->id + "_DEFFUSE", texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Deffuse->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));
}

void BillboardSprite::setNormalTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Normal = new TextureAtlas(this->id + "_NORMAL", texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Normal->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));
}

void BillboardSprite::setOcclusionTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Occlusion = new TextureAtlas(this->id + "_OCCLUSION", texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Occlusion->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));
}

void BillboardSprite::setSpecularTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Specular = new TextureAtlas(this->id + "_SPECULAR", texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Specular->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));
}

void BillboardSprite::setDeffuseTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Deffuse = textureAtlas;
}

void BillboardSprite::setNormalTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Normal = textureAtlas;
}

void BillboardSprite::setOcclusionTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Occlusion = textureAtlas;
}

void BillboardSprite::setSpecularTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Specular = textureAtlas;
}

void BillboardSprite::setSceneCamera(raylib::Camera3D* camera) {
    this->camera3D = camera;
}

void BillboardSprite::setRenderMode(BILLBOARD_RENDER_MODE mode) {
    this->renderMode = mode;
}

void BillboardSprite::playAnimation(std::string animationID) {
    this->playing = true;
    SpriteAnimation* spriteAnimation = this->textureAtlas_Deffuse->getAnimation(animationID);
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

    raylib::Texture2D* atlasTexture = this->textureAtlas_Deffuse->getAtlasTexture();
    
    switch (this->renderMode) {
        case DEFFUSE:
            atlasTexture = this->textureAtlas_Deffuse->getAtlasTexture();
            break;

        case NORMAL:
            atlasTexture = this->textureAtlas_Normal->getAtlasTexture();
            break;

        case OCCLUSION:
            atlasTexture = this->textureAtlas_Occlusion->getAtlasTexture();
            break;

        case SPECULAR:
            atlasTexture = this->textureAtlas_Specular->getAtlasTexture();
            break;
    }

    this->calculateRenderedPosition();

    if (atlasTexture->IsValid() && this->currentFrameID != "") {
        this->drawBillboardTexture(atlasTexture);
    }
}

void BillboardSprite::drawBillboardTexture(raylib::Texture2D* atlasTexture) {
    raylib::Rectangle frameRect = this->textureAtlas_Deffuse->getFrameRect(this->currentFrameID);
    bool isFrameRotated = this->textureAtlas_Deffuse->getFrameRotated(this->currentFrameID);

    raylib::Vector2 calculatedScale{0.0f, 0.0f};
    float invertedTextureScale = 1 / this->textureAtlas_Deffuse->getTextureScale();

    if (isFrameRotated) {
        calculatedScale = raylib::Vector2(
            this->getScaleX() * invertedTextureScale, 
            (frameRect.height/frameRect.width) * this->getScaleY() * invertedTextureScale
        );
    } else {
        calculatedScale = raylib::Vector2(
            (frameRect.width/frameRect.height) * this->getScaleX() * invertedTextureScale, 
            this->getScaleY() * invertedTextureScale
        );
    }

    // the forward direction of the camera (look direction)
    Vector3 forward = Vector3Subtract(this->camera3D->target, this->camera3D->position);
    
    // the up vector we start with - but this up vector is not orthogonal to the forward vector
    Vector3 up = { 0.0f, 1.0f, 0.0f };
    
    // compute the right vector using the cross product of the up and forward vector
    // this vector is orthogonal to the forward vector
    Vector3 right = Vector3CrossProduct(up, forward);
    
    // compute the up vector using the cross product of the forward and right vector
    // the result is orthogonal to the forward and right vector, so it's now pointing up in 
    // the orientation of the camera itself
    up = Vector3CrossProduct(forward, right);
    
    // normalize the up vector so it's unit length
    up = Vector3Normalize(up);

    atlasTexture->DrawBillboard(
        *this->camera3D, 
        frameRect, 
        raylib::Vector3(this->getX(), this->getY(), this->getZ()), 
        up, 
        calculatedScale,
        raylib::Vector2(0.5f, 0.5f),
        this->getRotation() + (isFrameRotated ? 90 : 0),
        raylib::Color::White()
    );
}