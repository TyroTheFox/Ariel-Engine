#include <engine/render/scene_renderer_3D.h>

SceneRenderer3D::SceneRenderer3D(int screenWidth, int screenHeight) {
    this->defferredShader = new RenderingShader(
        "resources/shaders/glsl%i/deferred_shading/deferred_shading.vs",
        "resources/shaders/glsl%i/deferred_shading/deferred_shading.fs"
    );

    this->gBufferShader = new RenderingShader(
        "resources/shaders/glsl%i/gbuffer/gbuffer.vs",
        "resources/shaders/glsl%i/gbuffer/gbuffer.fs"
    );

    this->gBufferInstance = new GraphicsBuffer(this->defferredShader, screenWidth, screenHeight);
}

SceneRenderer3D::~SceneRenderer3D()
{
}