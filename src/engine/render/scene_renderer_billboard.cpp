#include <engine/render/scene_renderer_billboard.h>

SceneRendererBillboard::SceneRendererBillboard() {
    ShaderManager shadermanager = ShaderManager();

    this->billboardShader = shadermanager.getShaderPtr("billboard");
    this->billboardPosition = shadermanager.getShaderPtr("billboard_position");
    this->gBuffer = shadermanager.getShaderPtr("gBuffer");
    this->mixTexture = shadermanager.getShaderPtr("mix_texture");

    this->lightList = std::vector<Light>{};

    this->falloff = raylib::Vector3{0.4f, 3.0f, 20.0f};

    this->ambientColor = raylib::Color::White();

    this->positionRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->albedoRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->normalRenderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
}

SceneRendererBillboard::~SceneRendererBillboard() {
    delete this->billboardShader;

    this->lightList.clear();
}

void SceneRendererBillboard::createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, float intensity, raylib::Color color) {
    Light newLight = Light(id, type, this->lightList.size(), position, target, intensity, color, &this->billboardShader->shaderInstance);
    this->lightList.push_back(newLight);
}

void SceneRendererBillboard::setUpRenderer() {
    this->texAlbedoLoc = this->billboardShader->getShaderLocation("texture0");
    this->texNormalLoc = this->billboardShader->getShaderLocation("texture1");

    int gammaLoc = this->billboardShader->getShaderLocation("gamma");
    float gammaValue = GAMMA;
    this->billboardShader->setShaderValue(gammaLoc, &gammaValue, SHADER_UNIFORM_FLOAT);

    int exposureLoc = this->billboardShader->getShaderLocation("exposure");
    float exposureValue = HDR_EXPOSURE;
    this->billboardShader->setShaderValue(exposureLoc, &exposureValue, SHADER_UNIFORM_FLOAT);

    int falloffLoc = this->billboardShader->getShaderLocation("falloff");
    this->billboardShader->setShaderValue(falloffLoc, &this->falloff, SHADER_UNIFORM_VEC3);

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
}

void SceneRendererBillboard::setUpLights(raylib::Camera3D* camera) {
    float cameraPos[3] = { camera->position.x, camera->position.y, camera->position.z };
    this->billboardShader->setShaderValue(this->billboardShader->getShaderLocation(SHADER_LOC_VECTOR_VIEW), cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < this->lightList.size(); i++) {
        this->lightList.at(i).UpdateLightValues(&this->billboardShader->shaderInstance);
    }
}

void SceneRendererBillboard::beginPositionTextureRender(raylib::Camera3D* camera) {
    // ::BeginTextureMode(this->positionRenderTexture);
        camera->BeginMode();
            this->billboardPosition->shaderInstance.BeginMode();
}

void SceneRendererBillboard::endPositionTextureRender(raylib::Camera3D* camera) {
            this->billboardPosition->shaderInstance.EndMode();
        camera->EndMode();
    // ::EndTextureMode();
}

void SceneRendererBillboard::beginAlbedoTextureRender(raylib::Camera3D* camera) {
    ::BeginTextureMode(this->albedoRenderTexture);
        camera->BeginMode();
}

void SceneRendererBillboard::endAlbedoTextureRender(raylib::Camera3D* camera) {
        camera->EndMode();
    ::EndTextureMode();
}

void SceneRendererBillboard::beginNormalTextureRender(raylib::Camera3D* camera) {
    ::BeginTextureMode(this->normalRenderTexture);
        camera->BeginMode();
}

void SceneRendererBillboard::endNormalTextureRender(raylib::Camera3D* camera) {
        camera->EndMode();
    ::EndTextureMode();
}

void SceneRendererBillboard::beginRender(raylib::Camera3D* camera) {
    int textureActiveSlot = 1;
    camera->BeginMode();
        this->gBuffer->enableShader();          
}

void SceneRendererBillboard::endRender(raylib::Camera3D* camera) {
        this->gBuffer->disableShader();
    camera->EndMode();
}