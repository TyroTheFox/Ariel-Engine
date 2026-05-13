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

    this->gBufferInstance = new GraphicsBuffer(this->deferredShader);

    this->lightList = std::vector<Light*>();

    this->currentMode = DEFERRED_SHADING;

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

void SceneRenderer3D::render(raylib::Camera3D* camera, const Scene* renderedScene) {
    this->gBufferInstance->readyForDrawing();

    // Base Render Pass
    camera->BeginMode();
        gBufferShader->enableShader();
            renderedScene->signal_render_3D.emit();
        gBufferShader->disableShader();
    camera->EndMode();

    this->gBufferInstance->enableColorBlending();

    this->gBufferInstance->endBufferDrawing();

    camera->BeginMode();
        rlDisableColorBlend();
        rlEnableShader(this->deferredShader->getID());
        // Bind our g-buffer textures
        // We are binding them to locations that we earlier set in sampler2D uniforms `gPosition`, `gNormal`,
        // and `gAlbedoSpec`
        this->gBufferInstance->bindPositionTexture();
        this->gBufferInstance->bindNormalTexture();
        this->gBufferInstance->bindAlbedoTexture();

        // Finally, we draw a fullscreen quad to our default framebufferId
        // This will now be shaded using our deferred shader
        rlLoadDrawQuad();
        rlDisableShader();
        rlEnableColorBlend();
    camera->EndMode();

    this->gBufferInstance->blitBuffer();
}