#include <engine/actors/3D/mesh.h>

MeshModel::MeshModel(std::string id, raylib::Model* model) {
    this->id = id;

    this->setDefaults();

    this->model = model;
}

MeshModel::MeshModel(std::string id, raylib::Model* model, raylib::Texture* texturePtr) {
    this->id = id;

    this->setDefaults();

    this->textureAtlas = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));

    this->model = model;

    this->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *this->textureAtlas->getAtlasTexture();
}

MeshModel::MeshModel(std::string id, raylib::Model* model, TextureAtlas* textureAtlasPtr) {
    this->id = id;

    this->textureAtlas = textureAtlasPtr;

    this->setDefaults();

    this->model = model;

    this->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *this->textureAtlas->getAtlasTexture();
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
            this->model->Draw(this->positionVector, this->rotationAxis, this->rotation, this->scaleVector, this->tint);
        } else {
            this->model->Draw(this->positionVector, this->rotationAxis, this->rotation, this->scaleVector, this->tint);
        }
    }
}