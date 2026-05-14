#include <engine/actors/3D/mesh.h>

MeshModel::MeshModel(std::string id, raylib::Model* model) {
    this->id = id;
    this->actorType = "MeshModel";

    this->setDefaults();

    this->model = model;

    this->setModelTextures();
}

MeshModel::MeshModel(std::string id, raylib::Model* model, raylib::Texture* texturePtr) {
    this->id = id;
    this->actorType = "MeshModel";

    this->setDefaults();

    this->textureAtlas_Albedo = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Albedo->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model = model;

    this->setModelTextures();
}

MeshModel::MeshModel(std::string id, raylib::Model* model, TextureAtlas* textureAtlasPtr) {
    this->id = id;
    this->actorType = "MeshModel";

    this->textureAtlas_Albedo = textureAtlasPtr;

    this->setDefaults();

    this->model = model;

    this->setModelTextures();
}

void MeshModel::setDefaults() {
    this->actorRenderType = ACTOR_3D;
    
    this->positionVector = Vector3();
    this->scaleVector = Vector3();
    
    this->rotationAxis = Vector3();
    this->rotationAxis.x = 0;
    this->rotationAxis.y = 1;
    this->rotationAxis.z = 0;

    this->tint = raylib::Color::White();
    this->emissionTint = raylib::Color::White();

    this->tilingVector = Vector2();
    tilingVector.x = 0.5;
    tilingVector.y = 0.5;

    this->wireframeMode = false;
}

void MeshModel::setModelTextures() {
    this->textureAtlas_Metalness = this->textureAtlas_Albedo;
    this->textureAtlas_Normal = this->textureAtlas_Albedo;
    this->textureAtlas_Emission = this->textureAtlas_Albedo;

    // Setup materials[0].maps default parameters
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].color = this->tint;
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value = this->metalness;
    this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = this->roughness;
    this->model->materials[0].maps[MATERIAL_MAP_OCCLUSION].value = this->occlusion;
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color = this->emissionTint;

    // this->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *this->textureAtlas->getAtlasTexture();

    // Setup materials[0].maps default textures
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas_Albedo->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas_Metalness->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas_Normal->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas_Emission->getAtlasTexture();
}

MeshModel::~MeshModel() {
    this->model->materials[0].shader = Shader{ 0 };
    UnloadMaterial(this->model->materials[0]);
    this->model->materials[0].maps = NULL;
}

void MeshModel::setModel(raylib::Model* model) {
    this->model = model;
}

void MeshModel::setAlbedoTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Albedo = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Albedo->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas_Albedo->getAtlasTexture();
}

void MeshModel::setMetalnessTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Metalness = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Metalness->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas_Metalness->getAtlasTexture();
}

void MeshModel::setNormalTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Normal = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Normal->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas_Normal->getAtlasTexture();
}

void MeshModel::setEmissionTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Emission = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Emission->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas_Emission->getAtlasTexture();
}

void MeshModel::setAlbedoTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Albedo = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas_Albedo->getAtlasTexture();
}

void MeshModel::setMetalnessTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Metalness = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas_Metalness->getAtlasTexture();
}

void MeshModel::setNormalTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Normal = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas_Normal->getAtlasTexture();
}

void MeshModel::setEmissionTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Emission = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas_Emission->getAtlasTexture();
}

TextureAtlas* MeshModel::getTextureAtlas() {
    return this->textureAtlas_Albedo;
}

TextureAtlas* MeshModel::getMetalnessTextureAtlas() {
    return this->textureAtlas_Metalness;
}

TextureAtlas* MeshModel::getNormalTextureAtlas() {
    return this->textureAtlas_Normal;
}

TextureAtlas* MeshModel::getEmissionTextureAtlas() {
    return this->textureAtlas_Emission;
}

void MeshModel::setMetalness(float value) {
    this->metalness = value;
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value = this->metalness;
}

void MeshModel::setRoughness(float value) {
    this->roughness = value;
    this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = this->roughness;
}

void MeshModel::setOcclusion(float value) {
    this->occlusion = value;
    this->model->materials[0].maps[MATERIAL_MAP_OCCLUSION].value = this->occlusion;
}

void MeshModel::setEmissionColor(raylib::Color color) {
    this->emissionTint = color;
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color = this->emissionTint;
}

void MeshModel::setWireframeMode(bool wireframeMode) {
    this->wireframeMode = wireframeMode;
}

void MeshModel::setTint(raylib::Color tintColor) {
    this->tint = tintColor;
}

void MeshModel::setRotationAxis(float x, float y, float z) {
    this->rotationAxis.x = x;
    this->rotationAxis.y = y;
    this->rotationAxis.z = z;
}

void MeshModel::setRotationAxis(Vector3 vector) {
    this->rotationAxis = vector;
}

void MeshModel::update(float dT) {}

void MeshModel::render(RenderingShader* shader) {
    if (!this->getVisible()) {
        return;
    }

    // Get location for shader parameters that can be modified in real time
    int metallicValueLoc = shader->getShaderLocation("metallicValue");
    int roughnessValueLoc = shader->getShaderLocation("roughnessValue");
    int emissiveIntensityLoc = shader->getShaderLocation("emissivePower");
    int emissiveColorLoc = shader->getShaderLocation("emissiveColor");
    int textureTilingLoc = shader->getShaderLocation("tiling");

    this->model->materials[0].shader = shader->shaderInstance;

    // Set old car model texture tiling, emissive color and emissive intensity parameters on shader
    shader->setShaderValue(textureTilingLoc, &this->tilingVector, SHADER_UNIFORM_VEC2);

    Vector4 emissiveColor = ColorNormalize(this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color);
    shader->setShaderValue(emissiveColorLoc, &emissiveColor, SHADER_UNIFORM_VEC4);

    shader->setShaderValue(emissiveIntensityLoc, &this->emissiveIntensity, SHADER_UNIFORM_FLOAT);

    // Set old car metallic and roughness values
    shader->setShaderValue(metallicValueLoc, &this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value, SHADER_UNIFORM_FLOAT);
    shader->setShaderValue(roughnessValueLoc, &this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value, SHADER_UNIFORM_FLOAT);

    this->calculateRenderedPosition();

    this->positionVector.x = this->getX();
    this->positionVector.y = this->getY();
    this->positionVector.z = this->getZ();

    this->scaleVector.x = this->getScaleX();
    this->scaleVector.y = this->getScaleY();
    this->scaleVector.z = this->getScaleZ();

    if (this->model->IsValid()) {
        if (this->wireframeMode) {
            this->model->DrawWires(this->positionVector, this->rotationAxis, this->rotation, this->scaleVector, this->tint);
        } else {
            this->model->Draw(this->positionVector, this->rotationAxis, this->rotation, this->scaleVector, this->tint);
        }
    }
}