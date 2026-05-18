#include <engine/render/scene_renderer_3D.h>

SceneRenderer3D::SceneRenderer3D() {
    ShaderManager shadermanager = ShaderManager();

    this->gBuffer = shadermanager.getShaderPtr("gbuffer");
    this->deferredShader = shadermanager.getShaderPtr("deferred");

    this->lightList = std::vector<Light*>{};

    this->ambientColor = raylib::Color::White();

    this->graphicsBuffer = new GraphicsBuffer(this->deferredShader);
}

SceneRenderer3D::~SceneRenderer3D() {
    delete this->gBuffer;
    delete this->deferredShader;

    for (int i = 0; i < this->lightList.size(); i++) {
        delete this->lightList.at(i);
    }

    this->lightList.clear();
}

void SceneRenderer3D::createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, float intensity, raylib::Color color) {
    Light* newLight = new Light(id, type, this->lightList.size(), position, target, intensity, color, &this->deferredShader->shaderInstance);
    this->lightList.push_back(newLight);
}

void SceneRenderer3D::setUpRenderer() {
    int gammaLoc = this->deferredShader->getShaderLocation("gamma");

    this->deferredShader->setShaderValue(gammaLoc, &this->gammaValue, SHADER_UNIFORM_FLOAT);

    // Setup additional required shader locations, including lights data
    int lightCountLoc = GetShaderLocation(this->deferredShader->shaderInstance, "numOfLights");
    int maxLightCount = this->lightList.size();
    this->deferredShader->setShaderValue(lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

    // Setup ambient color and intensity parameters
    Vector3 ambientColorNormalized = (Vector3){ this->ambientColor.r/255.0f, this->ambientColor.g/255.0f, this->ambientColor.b/255.0f };
    this->deferredShader->setShaderValue("ambientColor", &ambientColorNormalized, SHADER_UNIFORM_VEC3);
    this->deferredShader->setShaderValue("ambient", &this->ambientIntensity, SHADER_UNIFORM_FLOAT);

    ::rlEnableDepthTest();
}

void SceneRenderer3D::beginRender(raylib::Camera3D* camera) {
    float cameraPos[3] = { camera->position.x, camera->position.y, camera->position.z };
    this->deferredShader->setShaderValue(this->deferredShader->getShaderLocation(SHADER_LOC_VECTOR_VIEW), cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < this->lightList.size(); i++) {
        this->lightList.at(i)->UpdateLightValues(&this->deferredShader->shaderInstance);
    }

    this->graphicsBuffer->readyForDrawing();

    // Base Render Pass
    camera->BeginMode();
        this->gBuffer->enableShader();
}

void SceneRenderer3D::endRenderAndProcess(raylib::Camera3D* camera) {
        this->gBuffer->disableShader();
    camera->EndMode();

    this->graphicsBuffer->enableColorBlending();

    this->graphicsBuffer->endBufferDrawing();

    camera->BeginMode();
        this->graphicsBuffer->disableColorBlending();
            this->deferredShader->enableShader();
                this->graphicsBuffer->bindPositionTexture();
                this->graphicsBuffer->bindNormalTexture();
                this->graphicsBuffer->bindAlbedoTexture();
                this->graphicsBuffer->bindEmissiveTexture();
                this->graphicsBuffer->bindMRATexture();
                ::rlLoadDrawQuad();
            this->deferredShader->disableShader();
        this->graphicsBuffer->enableColorBlending();
    camera->EndMode();

    this->graphicsBuffer->blitBuffer();
}
