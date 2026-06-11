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

    this->billboardGbuffer = shaderManager.getShaderPtr("gbuffer_billboard");

    this->matModelLoc_gBuffer = this->billboardGbuffer->getShaderLocation("modelMatrix");

    this->setUseOfTexture("useTexAlbedo", 1);
    this->setUseOfTexture("useTexNormal", 0);
    this->setUseOfTexture("useTexSpecular", 0);
    this->setUseOfTexture("useTexOcclusion", 0);

    this->defuseLoc = this->billboardGbuffer->getShaderLocation("albedoMap");
    this->normalLoc = this->billboardGbuffer->getShaderLocation("normalMap");
    this->specularLoc = this->billboardGbuffer->getShaderLocation("specularMap");
    this->occlusionLoc = this->billboardGbuffer->getShaderLocation("occlusionMap");
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

    this->setUseOfTexture("useTexAlbedo", 1);
}

void BillboardSprite::setNormalTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Normal = new TextureAtlas(this->id + "_NORMAL", texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Normal->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->setUseOfTexture("useTexNormal", 1);
}

void BillboardSprite::setOcclusionTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Occlusion = new TextureAtlas(this->id + "_OCCLUSION", texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Occlusion->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->setUseOfTexture("useTexOcclusion", 1);
}

void BillboardSprite::setSpecularTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Specular = new TextureAtlas(this->id + "_SPECULAR", texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Specular->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->setUseOfTexture("useTexSpecular", 1);
}

void BillboardSprite::setDeffuseTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Deffuse = textureAtlas;

    this->setUseOfTexture("useTexAlbedo", 1);
}

void BillboardSprite::setNormalTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Normal = textureAtlas;

    this->setUseOfTexture("useTexNormal", 1);
}

void BillboardSprite::setOcclusionTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Occlusion = textureAtlas;

    this->setUseOfTexture("useTexOcclusion", 1);
}

void BillboardSprite::setSpecularTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Specular = textureAtlas;

    this->setUseOfTexture("useTexSpecular", 1);
}

void BillboardSprite::setUseOfTexture(std::string uniformName, int useInt) {
    this->billboardGbuffer->setShaderValue(uniformName, &useInt, SHADER_UNIFORM_INT);
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

void BillboardSprite::calculateModelMatrix(Vector3 up, Vector3 right, Vector3 forward, Vector2 calculatedScale) {
    Matrix matScale = MatrixScale(this->getScaleX(), this->getScaleY(), this->getScaleZ());
    Matrix matRotation = MatrixRotate(up, this->rotation*DEG2RAD);
    Matrix matTranslation = MatrixTranslate(this->getX(), this->getY(), this->getZ());

    this->modelMatrix = MatrixMultiply(MatrixMultiply(matScale, matRotation), matTranslation);
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

    this->calculateRenderedPosition();

    if (atlasTexture->IsValid() && this->currentFrameID != "") {
        int emissiveIntensityLoc = this->billboardGbuffer->getShaderLocation("emissivePower");
        int metallicValueLoc = this->billboardGbuffer->getShaderLocation("metallicValue");
        int roughnessValueLoc = this->billboardGbuffer->getShaderLocation("roughnessValue");
        int aoValueLoc = this->billboardGbuffer->getShaderLocation("aoValue");

        this->billboardGbuffer->setShaderValue(metallicValueLoc, &this->metalness, SHADER_UNIFORM_FLOAT);
        this->billboardGbuffer->setShaderValue(roughnessValueLoc, &this->roughness, SHADER_UNIFORM_FLOAT);
        this->billboardGbuffer->setShaderValue(aoValueLoc, &this->occlusion, SHADER_UNIFORM_FLOAT);

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

    this->calculateModelMatrix(up, right, forward, calculatedScale);

    this->billboardGbuffer->setShaderMatrixValue(this->matModelLoc_gBuffer, this->modelMatrix);

    this->renderBillboardTextureObject(
        *this->camera3D,
        *atlasTexture,
        frameRect,
        raylib::Vector3(this->getX(), this->getY(), this->getZ()),
        up,
        calculatedScale,
        raylib::Vector2(0.5f, 0.5f),
        this->getRotation() + (isFrameRotated ? 90 : 0),
        raylib::Color::White()
    );
}

void BillboardSprite::renderBillboardTextureObject(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint) {
    // Compute the up vector and the right vector
    Matrix matView = MatrixLookAt(camera.position, camera.target, camera.up);
    Vector3 right = { matView.m0, matView.m4, matView.m8 };
    right = Vector3Scale(right, size.x);
    up = Vector3Scale(up, size.y);

    // Flip the content of the billboard while maintaining the counterclockwise edge rendering order
    if (size.x < 0.0f)
    {
        source.x -= size.x;
        source.width *= -1.0;
        right = Vector3Negate(right);
        origin.x *= -1.0f;
    }
    if (size.y < 0.0f)
    {
        source.y -= size.y;
        source.height *= -1.0;
        up = Vector3Negate(up);
        origin.y *= -1.0f;
    }

    // Draw the texture region described by source on the following rectangle in 3D space:
    //
    //                size.x          <--.
    //  3 ^---------------------------+ 2 \ rotation
    //    |                           |   /
    //    |                           |
    //    |   origin.x   position     |
    // up |..............             | size.y
    //    |             .             |
    //    |             . origin.y    |
    //    |             .             |
    //  0 +---------------------------> 1
    //                right
    Vector3 forward;
    if (rotation != 0.0) forward = Vector3CrossProduct(right, up);

    Vector3 origin3D = Vector3Add(Vector3Scale(Vector3Normalize(right), origin.x), Vector3Scale(Vector3Normalize(up), origin.y));

    Vector3 points[4];
    points[0] = Vector3Zero();
    points[1] = right;
    points[2] = Vector3Add(up, right);
    points[3] = up;

    for (int i = 0; i < 4; i++)
    {
        points[i] = Vector3Subtract(points[i], origin3D);
        if (rotation != 0.0) points[i] = Vector3RotateByAxisAngle(points[i], forward, rotation*DEG2RAD);
        points[i] = Vector3Add(points[i], position);
    }

    Vector3 normals[4];

    normals[0] = this->calculateNormalFromPoints(points[0], points[1], points[3]);
    normals[1] = this->calculateNormalFromPoints(points[1], points[2], points[0]);
    normals[2] = this->calculateNormalFromPoints(points[2], points[3], points[1]);
    normals[3] = this->calculateNormalFromPoints(points[3], points[0], points[2]);

    Vector2 texcoords[4];
    texcoords[0] = (Vector2){ (float)source.x/texture.width, (float)(source.y + source.height)/texture.height };
    texcoords[1] = (Vector2){ (float)(source.x + source.width)/texture.width, (float)(source.y + source.height)/texture.height };
    texcoords[2] = (Vector2){ (float)(source.x + source.width)/texture.width, (float)source.y/texture.height };
    texcoords[3] = (Vector2){ (float)source.x/texture.width, (float)source.y/texture.height };
    
    Texture2D SPECULARTEX = *this->textureAtlas_Specular->getAtlasTexture();
    Texture2D NORMALTEX = *this->textureAtlas_Normal->getAtlasTexture();
    Texture2D OCCLUSIONTEX = *this->textureAtlas_Occlusion->getAtlasTexture();

    this->billboardGbuffer->setShaderTextureValue(this->normalLoc, NORMALTEX);
    this->billboardGbuffer->setShaderTextureValue(this->specularLoc, SPECULARTEX);
    this->billboardGbuffer->setShaderTextureValue(this->occlusionLoc, OCCLUSIONTEX);

    rlSetTexture(texture.id);

    // Deffuse
    // int DEFFUSE = MATERIAL_MAP_ALBEDO;
    // rlActiveTextureSlot(DEFFUSE);
    // rlEnableTexture(texture.id);
    // rlSetUniform(RL_SHADER_LOC_MAP_ALBEDO, &DEFFUSE, SHADER_UNIFORM_INT, 1);

    // int SPECULAR = MATERIAL_MAP_METALNESS;
    // rlActiveTextureSlot(SPECULAR);
    // rlEnableTexture(SPECULARTEXID);
    // rlSetUniform(RL_SHADER_LOC_MAP_SPECULAR, &SPECULAR, SHADER_UNIFORM_INT, 1);

    // int NORMAL = MATERIAL_MAP_NORMAL;
    // rlActiveTextureSlot(NORMAL);
    // rlEnableTexture(NORMALTEXID);
    // rlSetUniform(RL_SHADER_LOC_MAP_NORMAL, &NORMAL, SHADER_UNIFORM_INT, 1);

    // int OCCLUSION = MATERIAL_MAP_OCCLUSION;
    // rlActiveTextureSlot(OCCLUSION);
    // rlEnableTexture(OCCLUSIONTEXID);
    // rlSetUniform(RL_SHADER_LOC_MAP_OCCLUSION, &OCCLUSION, SHADER_UNIFORM_INT, 1);

    rlBegin(RL_QUADS);

        rlColor4ub(tint.r, tint.g, tint.b, tint.a);
        for (int i = 0; i < 4; i++)
        {
            rlTexCoord2f(texcoords[i].x, texcoords[i].y);
            rlVertex3f(points[i].x, points[i].y, points[i].z);
            rlNormal3f(normals[i].x, normals[i].y, normals[i].z);
        }

    rlEnd();
    rlSetTexture(0);

    // rlActiveTextureSlot(DEFFUSE);
    // rlDisableTexture();
    // rlActiveTextureSlot(SPECULAR);
    // rlDisableTexture();
    // rlActiveTextureSlot(NORMAL);
    // rlDisableTexture();
    // rlActiveTextureSlot(OCCLUSION);
    // rlDisableTexture();
}

Vector3 BillboardSprite::calculateNormalFromPoints(Vector3 v0, Vector3 v1, Vector3 v2) {
    Vector3 edge1 = Vector3Subtract(v1, v0);
    Vector3 edge2 = Vector3Subtract(v2, v0);
    Vector3 normal = Vector3Normalize(Vector3CrossProduct(edge1, edge2));

    return normal;
}