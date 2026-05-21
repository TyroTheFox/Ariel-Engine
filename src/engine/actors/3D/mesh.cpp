#include <engine/actors/3D/mesh.h>

MeshModel::MeshModel(std::string id, raylib::Model* model) {
    TextureAssetLoader textureAssetLoader = TextureAssetLoader();
    this->id = id;
    this->actorType = "MeshModel";

    this->setDefaults();

    raylib::Texture2D* texturePtr = textureAssetLoader.getTexturePtr("_DEFAULT_");
    
    this->textureAtlas_Albedo = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Albedo->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

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
    ShaderManager shadermanager = ShaderManager();

    this->gBufferShader = shadermanager.getShaderPtr("gbuffer");
    
    this->model->materials[0].shader = this->gBufferShader->shaderInstance;
    this->model->meshMaterial[0] = 0;

    // Get location for shader parameters that can be modified in real time 
    int metallicValueLoc = this->gBufferShader->getShaderLocation("metallicValue");
    int roughnessValueLoc = this->gBufferShader->getShaderLocation("roughnessValue");
    int aoValueLoc = this->gBufferShader->getShaderLocation("aoValue");
    int emissiveIntensityLoc = this->gBufferShader->getShaderLocation("emissivePower");
    int emissiveColorLoc = this->gBufferShader->getShaderLocation("emissiveColor");
    int textureTilingLoc = this->gBufferShader->getShaderLocation("tiling");

    // Setup material texture maps usage in shader
    // NOTE: By default, the texture maps are always used
    this->setUseOfTexture("useTexAlbedo", 1);
    this->setUseOfTexture("useTexNormal", 0);
    this->setUseOfTexture("useTexMRA", 0);
    this->setUseOfTexture("useTexEmissive", 0);

    this->textureAtlas_Metalness = this->textureAtlas_Albedo;
    this->textureAtlas_Normal = this->textureAtlas_Albedo;
    this->textureAtlas_Emission = this->textureAtlas_Albedo;

    // // Setup materials[0].maps default textures
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas_Albedo->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas_Metalness->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas_Normal->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas_Emission->getAtlasTexture();

    // Setup materials[0].maps default parameters
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].color = this->tint;
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value = this->metalness;
    this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = this->roughness;
    this->model->materials[0].maps[MATERIAL_MAP_OCCLUSION].value = this->occlusion;
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color = this->emissionTint;

    // Set old car metallic and roughness values
    this->gBufferShader->setShaderValue(metallicValueLoc, &this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value, SHADER_UNIFORM_FLOAT);
    this->gBufferShader->setShaderValue(roughnessValueLoc, &this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value, SHADER_UNIFORM_FLOAT);
    this->gBufferShader->setShaderValue(aoValueLoc, &this->model->materials[0].maps[MATERIAL_MAP_OCCLUSION].value, SHADER_UNIFORM_FLOAT);

        // Set old car model texture tiling, emissive color and emissive intensity parameters on shader
    this->gBufferShader->setShaderValue(textureTilingLoc, &this->tilingVector, SHADER_UNIFORM_VEC2);

    Vector4 emissiveColor = ColorNormalize(this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color);
    this->gBufferShader->setShaderValue(emissiveColorLoc, &emissiveColor, SHADER_UNIFORM_VEC4);

    this->gBufferShader->setShaderValue(emissiveIntensityLoc, &this->emissiveIntensity, SHADER_UNIFORM_FLOAT);
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

    this->setUseOfTexture("useTexMRA", 1);
}

void MeshModel::setNormalTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Normal = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Normal->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas_Normal->getAtlasTexture();

    this->setUseOfTexture("useTexNormal", 1);
}

void MeshModel::setEmissionTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas_Emission = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas_Emission->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas_Emission->getAtlasTexture();

    this->setUseOfTexture("useTexEmissive", 1);
}

void MeshModel::setAlbedoTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Albedo = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas_Albedo->getAtlasTexture();
}

void MeshModel::setMetalnessTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Metalness = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas_Metalness->getAtlasTexture();

    this->setUseOfTexture("useTexMRA", 1);
}

void MeshModel::setNormalTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Normal = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas_Normal->getAtlasTexture();

    this->setUseOfTexture("useTexNormal", 1);
}

void MeshModel::setEmissionTexture(TextureAtlas* textureAtlas) {
    this->textureAtlas_Emission = textureAtlas;

    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas_Emission->getAtlasTexture();

    this->setUseOfTexture("useTexEmissive", 1);
}

void MeshModel::setUseOfTexture(std::string uniformName, int useInt) {
    this->gBufferShader->setShaderValue(uniformName, &useInt, SHADER_UNIFORM_INT);
}

void MeshModel::setTextureTilingVector(float x, float y) {
    this->tilingVector.x = x;
    this->tilingVector.y = y;
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

void MeshModel::render() {
    if (!this->getVisible()) {
        return;
    }

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