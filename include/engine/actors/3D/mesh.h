#pragma once

#ifndef MESH_H
#define MESH_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>
#include <sling.h>

class MeshModel : public BaseActor {
private:
    TextureAtlas* textureAtlas;
    raylib::Model* model;

    raylib::Vector3 rotationAxis;
    raylib::Vector3 positionVector;
    raylib::Vector3 scaleVector;

    raylib::Color tint;

    bool wireframeMode;

    void setDefaults();
public:
    MeshModel(std::string id, raylib::Model* model);
    MeshModel(std::string id, raylib::Model* model, raylib::Texture* texturePtr);
    MeshModel(std::string id, raylib::Model* model, TextureAtlas* textureAtlasPtr);
    ~MeshModel();

    void setModel(raylib::Model* model);
    void setTexture(raylib::Texture2D* texturePtr);
    TextureAtlas* getTextureAtlas();

    void setWireframeMode(bool wireframeMode);
    void setTint(raylib::Color tint);

    void setRotationAxis(float x, float y, float z);
    void setRotationAxis(Vector3 vector);

    void update(float dT) override;
    void render() override;
};

#endif