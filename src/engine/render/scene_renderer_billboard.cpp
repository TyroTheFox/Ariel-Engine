#include <engine/render/scene_renderer_billboard.h>

SceneRendererBillboard::SceneRendererBillboard() {
    ShaderManager shadermanager = ShaderManager();

    this->billboardShader = shadermanager.getShaderPtr("billboard");
    this->billboardPosition = shadermanager.getShaderPtr("billboard_position");
    this->billboardNormal = shadermanager.getShaderPtr("billboard_normal");
    this->gBuffer = shadermanager.getShaderPtr("gbuffer_billboard");
    this->mixTexture = shadermanager.getShaderPtr("mix_texture");
    
    this->lightList = std::vector<Light>{};
    
    // this->falloff = raylib::Vector3{0.4f, 3.0f, 20.0f};
    
    this->ambientColor = raylib::Color::White();

    this->gBufferBillboard = new GraphicsBufferBillboard(this->billboardShader);
    
    this->positionRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->albedoRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->normalRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->occlusionRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->specularRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    this->finalTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
}

SceneRendererBillboard::~SceneRendererBillboard() {
    this->gBufferBillboard->readyForDrawing();
    this->gBufferBillboard->endBufferDrawing();

    delete this->billboardShader;

    UnloadRenderTexture(this->positionRenderTexture);
    UnloadRenderTexture(this->albedoRenderTexture);
    UnloadRenderTexture(this->normalRenderTexture);
    UnloadRenderTexture(this->occlusionRenderTexture);
    UnloadRenderTexture(this->specularRenderTexture);

    UnloadRenderTexture(this->finalTexture);

    this->lightList.clear();
}

void SceneRendererBillboard::createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, float intensity, raylib::Color color) {
    Light newLight = Light(id, type, this->lightList.size(), position, target, intensity, color, &this->billboardShader->shaderInstance);
    this->lightList.push_back(newLight);
}

void SceneRendererBillboard::setUpRenderer() {
    // this->texPositionLoc = this->billboardShader->getShaderLocation("gPosition");
    // this->texAlbedoLoc = this->billboardNormal->getShaderLocation("gAlbedo");
    // this->texNormalLoc = this->billboardShader->getShaderLocation("gNormal");
    // this->texOcclusionLoc = this->billboardShader->getShaderLocation("gSpecular");
    // this->texSpecularLoc = this->billboardShader->getShaderLocation("gOcclusion");

    int gammaLoc = this->billboardShader->getShaderLocation("gamma");
    float gammaValue = GAMMA;
    this->billboardShader->setShaderValue(gammaLoc, &gammaValue, SHADER_UNIFORM_FLOAT);

    int exposureLoc = this->billboardShader->getShaderLocation("exposure");
    float exposureValue = HDR_EXPOSURE;
    this->billboardShader->setShaderValue(exposureLoc, &exposureValue, SHADER_UNIFORM_FLOAT);

    // int falloffLoc = this->billboardShader->getShaderLocation("falloff");
    // this->billboardShader->setShaderValue(falloffLoc, &this->falloff, SHADER_UNIFORM_VEC3);

    int lightCountLoc = GetShaderLocation(this->billboardShader->shaderInstance, "numOfLights");
    int maxLightCount = this->lightList.size();
    this->billboardShader->setShaderValue(lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

    // Setup ambient color and intensity parameters
    Vector3 ambientColorNormalized = (Vector3){ this->ambientColor.r/255.0f, this->ambientColor.g/255.0f, this->ambientColor.b/255.0f };
    float ambientIntensity = AMBIENT_INTENSITY;
    Vector2 screenResolution = (Vector2){ SCREEN_WIDTH, SCREEN_HEIGHT };

    this->billboardShader->setShaderValue("ambientColor", &ambientColorNormalized, SHADER_UNIFORM_VEC3);
    this->billboardShader->setShaderValue("ambient", &ambientIntensity, SHADER_UNIFORM_FLOAT);
    this->billboardShader->setShaderValue("resolution", &screenResolution, SHADER_UNIFORM_VEC2);

    ::rlEnableDepthTest();

    this->gBufferBillboard->readyForDrawing();
    this->gBufferBillboard->endBufferDrawing();
}

void SceneRendererBillboard::setUpLights(raylib::Camera3D* camera) {
    float cameraPos[3] = { camera->position.x, camera->position.y, camera->position.z };
    this->billboardShader->setShaderValue(this->billboardShader->getShaderLocation(SHADER_LOC_VECTOR_VIEW), cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < this->lightList.size(); i++) {
        this->lightList.at(i).UpdateLightValues(&this->billboardShader->shaderInstance);
    }
}

void SceneRendererBillboard::beginPositionTextureRender(raylib::Camera3D* camera) {
    ::BeginTextureMode(this->positionRenderTexture);
        ::ClearBackground(raylib::Color::Blank());
        camera->BeginMode();
            this->billboardPosition->shaderInstance.BeginMode();
}

void SceneRendererBillboard::endPositionTextureRender(raylib::Camera3D* camera) {
            this->billboardPosition->shaderInstance.EndMode();
        camera->EndMode();
    ::EndTextureMode();
}

void SceneRendererBillboard::beginAlbedoTextureRender(raylib::Camera3D* camera) {
    ::BeginTextureMode(this->albedoRenderTexture);
        ::ClearBackground(raylib::Color::Blank());
        camera->BeginMode();
}

void SceneRendererBillboard::endAlbedoTextureRender(raylib::Camera3D* camera) {
        camera->EndMode();
    ::EndTextureMode();
}

void SceneRendererBillboard::beginNormalTextureRender(raylib::Camera3D* camera) {
    ::BeginTextureMode(this->normalRenderTexture);
        ::ClearBackground(raylib::Color::Blank());
        camera->BeginMode();
            this->billboardNormal->shaderInstance.BeginMode();
}

void SceneRendererBillboard::endNormalTextureRender(raylib::Camera3D* camera) {
            this->billboardNormal->shaderInstance.EndMode();
        camera->EndMode();
    ::EndTextureMode();
}

void SceneRendererBillboard::beginOcclusionTextureRender(raylib::Camera3D* camera) {
    ::BeginTextureMode(this->occlusionRenderTexture);
        ::ClearBackground(raylib::Color::Blank());
        camera->BeginMode();
}

void SceneRendererBillboard::endOcclusionTextureRender(raylib::Camera3D* camera) {
        camera->EndMode();
    ::EndTextureMode();
}

void SceneRendererBillboard::beginSpecularTextureRender(raylib::Camera3D* camera) {
    ::BeginTextureMode(this->specularRenderTexture);
        ::ClearBackground(raylib::Color::Blank());
        camera->BeginMode();
}

void SceneRendererBillboard::endSpecularTextureRender(raylib::Camera3D* camera) {
        camera->EndMode();
    ::EndTextureMode();
}

void SceneRendererBillboard::beginRender(raylib::Camera3D* camera) {
    // raylib::Texture2D albedoTexture = raylib::Texture2D(this->albedoRenderTexture.texture);
    // this->finalTexture.BeginMode();
    // ::ClearBackground(raylib::Color::Blank());
    camera->BeginMode();
        this->gBuffer->enableShader();
            this->gBufferBillboard->readyForDrawing();
            // this->billboardShader->setShaderTextureValue(this->texPositionLoc, this->positionRenderTexture.GetTexture());
            // // this->billboardNormal->setShaderTextureValue(this->texAlbedoLoc, this->albedoRenderTexture.GetTexture());
            // this->billboardShader->setShaderTextureValue(this->texNormalLoc, this->normalRenderTexture.GetTexture());
            // this->billboardShader->setShaderTextureValue(this->texOcclusionLoc, this->occlusionRenderTexture.GetTexture());
            // this->billboardShader->setShaderTextureValue(this->texSpecularLoc, this->specularRenderTexture.GetTexture());

            // albedoTexture.Draw(
            //     Rectangle{ 
            //         0, 0, 
            //         static_cast<float>(this->albedoRenderTexture.texture.width), 
            //         static_cast<float>(-this->albedoRenderTexture.texture.height) 
            //     },
            //     Vector2{ static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
            //     WHITE
            // );

            // ::DrawTextureRec(
            //     this->albedoRenderTexture.texture,
            //     Rectangle{ 
            //         0, 0, 
            //         static_cast<float>(this->albedoRenderTexture.texture.width), 
            //         static_cast<float>(-this->albedoRenderTexture.texture.height) 
            //     },
            //     Vector2{ static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
            //     WHITE
            // );

            // ::rlActiveTextureSlot(this->texPositionLoc);
            // ::rlEnableTexture(this->positionRenderTexture.GetId());

            // ::rlActiveTextureSlot(this->texAlbedoLoc);
            // ::rlEnableTexture(this->albedoRenderTexture.GetId());

            // ::rlActiveTextureSlot(this->texNormalLoc);
            // ::rlEnableTexture(this->normalRenderTexture.GetId());

            // ::rlActiveTextureSlot(this->texOcclusionLoc);
            // ::rlEnableTexture(this->occlusionRenderTexture.GetId());

            // ::rlActiveTextureSlot(this->texSpecularLoc);
            // ::rlEnableTexture(this->specularRenderTexture.GetId());

            // ::rlLoadDrawQuad();
}

void SceneRendererBillboard::endRender(raylib::Camera3D* camera) {
        this->gBuffer->disableShader();
    camera->EndMode();
    // this->finalTexture.EndMode();

    // camera->BeginMode();
        // ::rlDisableColorBlend();
        // ::DrawTextureRec(
        //     this->finalTexture.texture,
        //     Rectangle{ 
        //         0, 0, 
        //         static_cast<float>(this->finalTexture.texture.width), 
        //         static_cast<float>(-this->finalTexture.texture.height) 
        //     },
        //     Vector2{ 0, 0 },
        //     WHITE
        // );

        // DrawTexturePro(
        //     this->finalTexture.texture,
        //     raylib::Rectangle{ 
        //         0, 0, 
        //         static_cast<float>(this->finalTexture.texture.width), 
        //         static_cast<float>(-this->finalTexture.texture.height) 
        //     },
        //     raylib::Rectangle{ 
        //         0, 0, 
        //         static_cast<float>(this->finalTexture.texture.width), 
        //         static_cast<float>(-this->finalTexture.texture.height) 
        //     },
        //     raylib::Vector2{ 0, 0 },
        //     0,
        //     raylib::Color::White()
        // );
        // ::rlEnableColorBlend();
    // camera->EndMode();
}

void SceneRendererBillboard::processRender(raylib::Camera3D* camera) {
    this->gBufferBillboard->enableColorBlending();
    
    this->gBufferBillboard->endBufferDrawing();

    camera->BeginMode();
        this->gBufferBillboard->disableColorBlending();
            this->billboardShader->rlEnableShader();
                this->gBufferBillboard->bindPositionTexture();
                this->gBufferBillboard->bindNormalTexture();
                this->gBufferBillboard->bindAlbedoTexture();
                this->gBufferBillboard->bindOcclusionTexture();
                this->gBufferBillboard->bindSpecularTexture();
                ::rlLoadDrawQuad();
            this->billboardShader->rlDisableShader();
        this->gBufferBillboard->enableColorBlending();
    camera->EndMode();

    this->gBufferBillboard->blitBuffer();
}