#include <engine/render/scene_renderer_3D.h>

SceneRenderer3D::SceneRenderer3D() {
    this->pbrShader = new RenderingShader(
        "resources/shaders/glsl%i/pbr/pbr.vs",
        "resources/shaders/glsl%i/pbr/pbr.fs"
    );

    this->pbrShader->setShaderLocation(SHADER_LOC_MAP_ALBEDO, "albedoMap");

    // WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture
    // They are passed as to the SHADER_LOC_MAP_METALNESS location for convenience,
    // shader already takes care of it accordingly
    this->pbrShader->setShaderLocation(SHADER_LOC_MAP_METALNESS, "mraMap");
    this->pbrShader->setShaderLocation(SHADER_LOC_MAP_NORMAL, "normalMap");

    // WARNING: Similar to the MRA map, the emissive map packs different information
    // into a single texture: it stores height and emission data
    // It is binded to SHADER_LOC_MAP_EMISSION location an properly processed on shader
    this->pbrShader->setShaderLocation(SHADER_LOC_MAP_EMISSION, "emissiveMap");
    this->pbrShader->setShaderLocation(SHADER_LOC_COLOR_DIFFUSE, "albedoColor");

    this->lightList = std::vector<Light*>{};
}

SceneRenderer3D::~SceneRenderer3D() {
    delete this->pbrShader;

    for (int i = 0; i < this->lightList.size(); i++) {
        delete this->lightList.at(i);
    }

    this->lightList.clear();
}

void SceneRenderer3D::createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, float intensity, raylib::Color color) {
    Light* newLight = new Light(id, type, this->lightList.size(), position, target, intensity, color, &this->pbrShader->shaderInstance);
    this->lightList.push_back(newLight);
}

void SceneRenderer3D::setUpRenderer() {
    // Setup additional required shader locations, including lights data
    this->pbrShader->setShaderLocation(SHADER_LOC_VECTOR_VIEW, "viewPos");
    int lightCountLoc = GetShaderLocation(this->pbrShader->shaderInstance, "numOfLights");
    int maxLightCount = this->lightList.size();
    this->pbrShader->setShaderValue(lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

    // Setup ambient color and intensity parameters
    float ambientIntensity = 1.0f;
    Color ambientColor = (Color){ 255, 0, 0, 255 };
    Vector3 ambientColorNormalized = (Vector3){ ambientColor.r/255.0f, ambientColor.g/255.0f, ambientColor.b/255.0f };
    this->pbrShader->setShaderValue("ambientColor", &ambientColorNormalized, SHADER_UNIFORM_VEC3);
    this->pbrShader->setShaderValue("ambient", &ambientIntensity, SHADER_UNIFORM_FLOAT);

    // Setup material texture maps usage in shader
    // NOTE: By default, the texture maps are always used
    int usage = 1;
    this->pbrShader->setShaderValue("useTexAlbedo", &usage, SHADER_UNIFORM_INT);
    this->pbrShader->setShaderValue("useTexNormal", &usage, SHADER_UNIFORM_INT);
    this->pbrShader->setShaderValue("useTexMRA", &usage, SHADER_UNIFORM_INT);
    this->pbrShader->setShaderValue("useTexEmissive", &usage, SHADER_UNIFORM_INT);
}

void SceneRenderer3D::beginRender(raylib::Camera3D* camera) {
    float cameraPos[3] = { camera->position.x, camera->position.y, camera->position.z };
    this->pbrShader->setShaderValue(this->pbrShader->getShaderLocation(SHADER_LOC_VECTOR_VIEW), cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < this->lightList.size(); i++) {
        this->lightList.at(i)->UpdateLightValues(&this->pbrShader->shaderInstance);
    }

    // Base Render Pass
    camera->BeginMode();
}

void SceneRenderer3D::endRenderAndProcess(raylib::Camera3D* camera) {
        // // Draw spheres to show the lights positions
        // for (int i = 0; i < this->lightList.size(); i++)
        // {
        //     Color lightColor = (Color){
        //         (unsigned char)(this->lightList.at(i)->getColor().r * 255),
        //         (unsigned char)(this->lightList.at(i)->getColor().g * 255),
        //         (unsigned char)(this->lightList.at(i)->getColor().b * 255),
        //         (unsigned char)(this->lightList.at(i)->getColor().a * 255)
        //     };

        //     if (this->lightList.at(i)->isEnabled()) DrawSphereEx(this->lightList.at(i)->getPosition(), 0.2f, 8, 8, lightColor);
        //     else DrawSphereWires(this->lightList.at(i)->getPosition(), 0.2f, 8, 8, ColorAlpha(lightColor, 0.3f));
        // }
    camera->EndMode();
}
