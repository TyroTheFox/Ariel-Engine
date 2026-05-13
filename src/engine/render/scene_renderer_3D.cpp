#include <engine/render/scene_renderer_3D.h>

SceneRenderer3D::SceneRenderer3D() {
    this->deferredShader = new RenderingShader(
        "resources/shaders/glsl%i/deferred_shading/deferred_shading.vs",
        "resources/shaders/glsl%i/deferred_shading/deferred_shading.fs"
    );

    this->gBufferShader = new RenderingShader(
        "resources/shaders/glsl%i/gbuffer/gbuffer.vs",
        "resources/shaders/glsl%i/gbuffer/gbuffer.fs"
    );

    this->deferredShader->setShaderLocation(SHADER_LOC_VECTOR_VIEW, "viewPosition");

    this->gBufferInstance = new GraphicsBuffer(this->deferredShader);

    this->lightList = std::vector<Light*>{};

    rlEnableDepthTest();
}

SceneRenderer3D::~SceneRenderer3D() {
    delete this->gBufferInstance;
    delete this->deferredShader;
    delete this->gBufferShader;

    for (int i = 0; i < this->lightList.size(); i++) {
        delete this->lightList.at(i);
    }

    this->lightList.clear();
}

void SceneRenderer3D::createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, raylib::Color color) {
    Light* newLight = new Light(id, type, this->lightList.size(), position, target, color, &this->deferredShader->shaderInstance);
    this->lightList.push_back(newLight);
}

void SceneRenderer3D::beginRender(raylib::Camera3D* camera) {
    float cameraPos[3] = { camera->position.x, camera->position.y, camera->position.z };
    this->deferredShader->setShaderValue(this->deferredShader->getShaderLocation(SHADER_LOC_VECTOR_VIEW), cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < this->lightList.size(); i++) {
        this->lightList.at(i)->UpdateLightValues(&this->deferredShader->shaderInstance);
    }
    
    this->gBufferInstance->readyForDrawing();

    // Base Render Pass
    camera->BeginMode();
        gBufferShader->enableShader();
}

void SceneRenderer3D::endRenderAndProcess(raylib::Camera3D* camera) {
        gBufferShader->disableShader();
    camera->EndMode();

    this->gBufferInstance->enableColorBlending();

    this->gBufferInstance->endBufferDrawing();

    camera->BeginMode();
        this->gBufferInstance->disableColorBlending();
        this->deferredShader->enableShader();
            // Bind our g-buffer textures
            // We are binding them to locations that we earlier set in sampler2D uniforms `gPosition`, `gNormal`,
            // and `gAlbedoSpec`
            this->gBufferInstance->bindPositionTexture();
            this->gBufferInstance->bindNormalTexture();
            this->gBufferInstance->bindAlbedoTexture();

        // Finally, we draw a fullscreen quad to our default framebufferId
        // This will now be shaded using our deferred shader
        ::rlLoadDrawQuad();
        this->deferredShader->disableShader();
        this->gBufferInstance->enableColorBlending();
    camera->EndMode();

    this->gBufferInstance->blitBuffer();
}
