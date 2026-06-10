#pragma once

#ifndef BILLBOARD_SPRITE_H
#define BILLBOARD_SPRITE_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>
#include <engine/render/shader_objects/rendering_shader.h>
#include <engine/render/shader_objects/shader_manager.h>

enum BILLBOARD_RENDER_MODE {
    POSITION,
    DEFFUSE,
    NORMAL,
    OCCLUSION,
    SPECULAR
};

class BillboardSprite : public BaseActor {
private:
    TextureAtlas* textureAtlas_Deffuse;
    TextureAtlas* textureAtlas_Normal;
    TextureAtlas* textureAtlas_Occlusion;
    TextureAtlas* textureAtlas_Specular;

    BILLBOARD_RENDER_MODE renderMode = DEFFUSE;

    std::string currentFrameID;
    std::string defaultAnimationID;
    int currentFrameIndex;

    SpriteAnimation* currentAnimation;

    RenderingShader* billboardPosition;
    RenderingShader* billboardNormal;

    RenderingShader* billboardGbuffer;

    int matModelLoc_Position = -1;
    int matModelLoc_Normal = -1;

    int matModelLoc_gBuffer = -1;
    int defuseLoc = -1;
    int normalLoc = -1;
    int occlusionLoc = -1;
    int specularLoc = -1;

    bool playing;

    int frameSpeedCount; 
    int loopCount;
    
    int metallicValueLoc = -1;
    int roughnessValueLoc = -1;
    int aoValueLoc = -1;
    int emissiveIntensityLoc = -1;
    int emissiveColorLoc = -1;
    int textureTilingLoc = -1;
    
    float metalness = 0.0f;
    float roughness = 0.5f;
    float occlusion = 0.5f;
    float emissiveIntensity = 0.5f;
    Vector2 tilingVector;

    void drawBillboardTexture(raylib::Texture2D* atlasTexture);
    void renderBillboardTextureObject(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint);
    Vector3 calculateNormalFromPoints(Vector3 v0, Vector3 v1, Vector3 v2);
    void generateMesh();
    void setUseOfTexture(std::string uniformName, int useInt);
public:
    // <Animation Name>
    sl::Signal<std::string> animationStarted;
    // <Animation Name>
    sl::Signal<std::string> animationStopped;
    // <Animation Name, Frame Index, DeltaTime>
    sl::Signal<std::string, int, float> animationUpdating;
    // <Animation Name, Loops Left>
    sl::Signal<std::string, int> animationLooped;

    sl::Slot<BILLBOARD_RENDER_MODE> onChangeRenderMode{this, &BillboardSprite::setRenderMode};

    raylib::Matrix modelMatrix;

    raylib::Camera3D* camera3D;

    raylib::Vector2 origin;

    BillboardSprite(std::string id, TextureAtlas* textureAtlas, std::string defaultAnimation = "default");
    ~BillboardSprite();

    void setDeffuseTexture(raylib::Texture2D* texturePtr);
    void setNormalTexture(raylib::Texture2D* texturePtr);
    void setOcclusionTexture(raylib::Texture2D* texturePtr);
    void setSpecularTexture(raylib::Texture2D* texturePtr);

    void setDeffuseTexture(TextureAtlas* textureAtlas);
    void setNormalTexture(TextureAtlas* textureAtlas);
    void setOcclusionTexture(TextureAtlas* textureAtlas);
    void setSpecularTexture(TextureAtlas* textureAtlas);

    void setSceneCamera(raylib::Camera3D* camera);

    void playAnimation(std::string animationID);
    void stopAnimation();

    void setRenderMode(BILLBOARD_RENDER_MODE mode);

    void calculateModelMatrix(Vector3 up, Vector3 right, Vector3 forward, Vector2 calculatedScale);

    void update(float dT) override;
    void render() override;
};

#endif