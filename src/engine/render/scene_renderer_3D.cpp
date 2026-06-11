#include <engine/render/scene_renderer_3D.h>

SceneRenderer3D::SceneRenderer3D() {
    ShaderManager shadermanager = ShaderManager();

    this->gBuffer = shadermanager.getShaderPtr("gbuffer");
    this->gBufferBill = shadermanager.getShaderPtr("gbuffer_billboard");

    this->deferredShader = shadermanager.getShaderPtr("deferred");

    this->lightList = std::vector<Light>{};

    this->ambientColor = raylib::Color::White();

    this->graphicsBuffer = new GraphicsBuffer();

    this->deferredShader->enableShader();
        int gPosition = rlGetLocationUniform(this->deferredShader->getID(), "gPosition");
        int gNormal = rlGetLocationUniform(this->deferredShader->getID(), "gNormal");
        int gAlbedo = rlGetLocationUniform(this->deferredShader->getID(), "gAlbedo");
        int gEmissive = rlGetLocationUniform(this->deferredShader->getID(), "gEmissive");
        int gMRA = rlGetLocationUniform(this->deferredShader->getID(), "gMRA");
        
        this->deferredShader->setShaderValue(gPosition, &this->graphicsBuffer->texUnitPosition, RL_SHADER_UNIFORM_SAMPLER2D);
        this->deferredShader->setShaderValue(gNormal, &this->graphicsBuffer->texUnitNormal, RL_SHADER_UNIFORM_SAMPLER2D);
        this->deferredShader->setShaderValue(gAlbedo, &this->graphicsBuffer->texUnitAlbedo, RL_SHADER_UNIFORM_SAMPLER2D);
        this->deferredShader->setShaderValue(gEmissive, &this->graphicsBuffer->texUnitEmissive, RL_SHADER_UNIFORM_SAMPLER2D);
        this->deferredShader->setShaderValue(gMRA, &this->graphicsBuffer->texUnitMRA, RL_SHADER_UNIFORM_SAMPLER2D);
    this->deferredShader->disableShader();
}

SceneRenderer3D::~SceneRenderer3D() {
    this->graphicsBuffer->readyForDrawing();
    this->graphicsBuffer->endBufferDrawing();

    delete this->gBuffer;
    delete this->gBufferBill;
    delete this->deferredShader;

    this->lightList.clear();
}

void SceneRenderer3D::createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, float intensity, raylib::Color color) {
    Light newLight = Light(id, type, this->lightList.size(), position, target, intensity, color);
    this->lightList.push_back(newLight);
}

void SceneRenderer3D::setUpRenderer() {
    this->setUpRendererShader(this->deferredShader);
}

void SceneRenderer3D::setUpRendererShader(RenderingShader* shader) {
    int gammaLoc = shader->getShaderLocation("gamma");
    float gammaValue = GAMMA;
    shader->setShaderValue(gammaLoc, &gammaValue, SHADER_UNIFORM_FLOAT);

    int exposureLoc = shader->getShaderLocation("exposure");
    float exposureValue = HDR_EXPOSURE;
    shader->setShaderValue(exposureLoc, &exposureValue, SHADER_UNIFORM_FLOAT);

    // Setup additional required shader locations, including lights data
    int lightCountLoc = GetShaderLocation(shader->shaderInstance, "numOfLights");
    int maxLightCount = this->lightList.size();
    shader->setShaderValue(lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

    // Setup ambient color and intensity parameters
    Vector3 ambientColorNormalized = (Vector3){ this->ambientColor.r/255.0f, this->ambientColor.g/255.0f, this->ambientColor.b/255.0f };
    float ambientIntensity = AMBIENT_INTENSITY;

    shader->setShaderValue("ambientColor", &ambientColorNormalized, SHADER_UNIFORM_VEC3);
    shader->setShaderValue("ambient", &ambientIntensity, SHADER_UNIFORM_FLOAT);

    ::rlEnableDepthTest();
}

void SceneRenderer3D::clearRenderer() {
    this->graphicsBuffer->readyForDrawing();
    this->graphicsBuffer->endBufferDrawing();
}

void SceneRenderer3D::setUpLighting(raylib::Camera3D* camera) {
    this->updatingLighting(camera, this->deferredShader);
}

void SceneRenderer3D::updatingLighting(raylib::Camera3D* camera, RenderingShader* shader) {
    float cameraPos[3] = { camera->position.x, camera->position.y, camera->position.z };
    shader->setShaderValue(shader->getShaderLocation(SHADER_LOC_VECTOR_VIEW), cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < this->lightList.size(); i++) {
        this->lightList.at(i).UpdateLightValues(&shader->shaderInstance);
    }
}

void SceneRenderer3D::readyBufferForDrawing() {
    this->graphicsBuffer->readyForDrawing();
    this->graphicsBuffer->disableColorBlending();
}

void SceneRenderer3D::beginRenderBillboard(raylib::Camera3D* camera) {
    // Base Render Pass
    camera->BeginMode();
        this->gBufferBill->enableShader();
}

void SceneRenderer3D::endRenderBillboard(raylib::Camera3D* camera) {
        this->gBufferBill->disableShader();
    camera->EndMode();
}

void SceneRenderer3D::beginRenderModel(raylib::Camera3D* camera) {
    // Base Render Pass
    camera->BeginMode();
        this->gBuffer->enableShader();
}

void SceneRenderer3D::endRenderModel(raylib::Camera3D* camera) {
        this->gBuffer->disableShader();
    camera->EndMode();
}

void SceneRenderer3D::processRender(raylib::Camera3D* camera) {
    this->graphicsBuffer->enableColorBlending();
    
    this->graphicsBuffer->endBufferDrawing();

    camera->BeginMode();
        this->graphicsBuffer->disableColorBlending();
            this->deferredShader->rlEnableShader();
                this->graphicsBuffer->bindPositionTexture();
                this->graphicsBuffer->bindNormalTexture();
                this->graphicsBuffer->bindAlbedoTexture();
                this->graphicsBuffer->bindEmissiveTexture();
                this->graphicsBuffer->bindMRATexture();
                ::rlLoadDrawQuad();
            this->deferredShader->rlDisableShader();
        this->graphicsBuffer->enableColorBlending();
    camera->EndMode();

    this->graphicsBuffer->blitBuffer();
}
