#include <engine/render/scene_renderer_3D.h>

SceneRenderer3D::SceneRenderer3D() {
    ShaderManager shadermanager = ShaderManager();

    this->pbrShader = shadermanager.getShaderPtr("pbr");

    this->lightList = std::vector<Light*>{};

    this->ambientColor = raylib::Color::White();
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
    int gammaLoc = this->pbrShader->getShaderLocation("gamma");

    this->pbrShader->setShaderValue(gammaLoc, &this->gammaValue, SHADER_UNIFORM_FLOAT);

    // Setup additional required shader locations, including lights data
    int lightCountLoc = GetShaderLocation(this->pbrShader->shaderInstance, "numOfLights");
    int maxLightCount = this->lightList.size();
    this->pbrShader->setShaderValue(lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

    // Setup ambient color and intensity parameters
    Vector3 ambientColorNormalized = (Vector3){ this->ambientColor.r/255.0f, this->ambientColor.g/255.0f, this->ambientColor.b/255.0f };
    this->pbrShader->setShaderValue("ambientColor", &ambientColorNormalized, SHADER_UNIFORM_VEC3);
    this->pbrShader->setShaderValue("ambient", &this->ambientIntensity, SHADER_UNIFORM_FLOAT);
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
