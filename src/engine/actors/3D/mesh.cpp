#include <engine/actors/3D/mesh.h>

MeshModel::MeshModel(std::string id, raylib::Model* model) {
    this->id = id;
    this->actorType = "MeshModel";

    this->setDefaults();

    this->model = model;

    // Setup materials[0].maps default parameters
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].color = this->tint;
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value = 1.0f;
    this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
    this->model->materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color = (Color){ 255, 162, 0, 255 };

    this->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *this->textureAtlas->getAtlasTexture();

    // Setup materials[0].maps default textures
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas->getAtlasTexture();
}

MeshModel::MeshModel(std::string id, raylib::Model* model, raylib::Texture* texturePtr) {
    this->id = id;
    this->actorType = "MeshModel";

    this->setDefaults();

    this->textureAtlas = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model = model;

    // Setup materials[0].maps default parameters
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].color = this->tint;
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value = 1.0f;
    this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
    this->model->materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color = (Color){ 255, 162, 0, 255 };

    this->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *this->textureAtlas->getAtlasTexture();

    // Setup materials[0].maps default textures
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas->getAtlasTexture();
}

MeshModel::MeshModel(std::string id, raylib::Model* model, TextureAtlas* textureAtlasPtr) {
    this->id = id;
    this->actorType = "MeshModel";

    this->textureAtlas = textureAtlasPtr;

    this->setDefaults();

    this->model = model;

    // Setup materials[0].maps default parameters
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].color = this->tint;
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].value = 1.0f;
    this->model->materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
    this->model->materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color = (Color){ 255, 162, 0, 255 };

    this->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *this->textureAtlas->getAtlasTexture();

    // Setup materials[0].maps default textures
    this->model->materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_METALNESS].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_NORMAL].texture = *this->textureAtlas->getAtlasTexture();
    this->model->materials[0].maps[MATERIAL_MAP_EMISSION].texture = *this->textureAtlas->getAtlasTexture();
}

void MeshModel::setDefaults() {
    this->actorRenderType = ACTOR_3D;
    
    this->positionVector = Vector3();
    this->scaleVector = Vector3();
    
    this->rotationAxis = Vector3();
    this->rotationAxis.x = 0;
    this->rotationAxis.y = 1;
    this->rotationAxis.z = 0;

    this->tint = raylib::Color::RayWhite();

    this->wireframeMode = false;
}

MeshModel::~MeshModel()
{
}

void MeshModel::setModel(raylib::Model* model) {
    this->model = model;
}

void MeshModel::setTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *this->textureAtlas->getAtlasTexture();
}

TextureAtlas* MeshModel::getTextureAtlas() {
    return this->textureAtlas;
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
    Vector2 tilingVector = Vector2();
    tilingVector.x = 0.5;
    tilingVector.y = 0.5;

    shader->setShaderValue(textureTilingLoc, &tilingVector, SHADER_UNIFORM_VEC2);

    Vector4 emissiveColor = ColorNormalize(this->model->materials[0].maps[MATERIAL_MAP_EMISSION].color);
    shader->setShaderValue(emissiveColorLoc, &emissiveColor, SHADER_UNIFORM_VEC4);

    float emissiveIntensity = 0.01f;
    shader->setShaderValue(emissiveIntensityLoc, &emissiveIntensity, SHADER_UNIFORM_FLOAT);

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
            this->model->Draw(this->positionVector, this->rotationAxis, this->rotation, this->scaleVector, this->tint);
        } else {
            this->model->Draw(this->positionVector, this->rotationAxis, this->rotation, this->scaleVector, this->tint);
        }
    }
}