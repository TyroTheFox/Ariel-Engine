#pragma once

#ifndef MESH_H
#define MESH_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>
#include <engine/render/rendering_shader.h>
#include <sling.h>

class MeshModel : public BaseActor {
protected:
    TextureAtlas* textureAtlas_Albedo;
    TextureAtlas* textureAtlas_Metalness;
    TextureAtlas* textureAtlas_Normal;
    TextureAtlas* textureAtlas_Emission;

    raylib::Model* model;

    raylib::Vector3 rotationAxis;
    raylib::Vector3 positionVector;
    raylib::Vector3 scaleVector;

    float metalness = 1.0f;
    float roughness = 1.0f;
    float occlusion = 1.0f;
    float emissiveIntensity = 0.01f;
    Vector2 tilingVector;

    raylib::Color tint;
    raylib::Color emissionTint;

    bool wireframeMode;

    void setDefaults();
    void setModelTextures();
public:
    MeshModel(std::string id, raylib::Model* model);
    MeshModel(std::string id, raylib::Model* model, raylib::Texture* texturePtr);
    MeshModel(std::string id, raylib::Model* model, TextureAtlas* textureAtlasPtr);
    ~MeshModel();

    void setModel(raylib::Model* model);

    void setAlbedoTexture(raylib::Texture2D* texturePtr);
    void setMetalnessTexture(raylib::Texture2D* texturePtr);
    void setNormalTexture(raylib::Texture2D* texturePtr);
    void setEmissionTexture(raylib::Texture2D* texturePtr);

    void setAlbedoTexture(TextureAtlas* textureAtlas);
    void setMetalnessTexture(TextureAtlas* textureAtlas);
    void setNormalTexture(TextureAtlas* textureAtlas);
    void setEmissionTexture(TextureAtlas* textureAtlas);

    TextureAtlas* getTextureAtlas();
    TextureAtlas* getMetalnessTextureAtlas();
    TextureAtlas* getNormalTextureAtlas();
    TextureAtlas* getEmissionTextureAtlas();

    void setMetalness(float value);
    void setRoughness(float value);
    void setOcclusion(float value);
    void setEmissionColor(raylib::Color color);

    void setWireframeMode(bool wireframeMode);
    void setTint(raylib::Color tint);

    void setRotationAxis(float x, float y, float z);
    void setRotationAxis(Vector3 vector);

    void update(float dT) override;
    void render(RenderingShader* shader) override;
};

#endif