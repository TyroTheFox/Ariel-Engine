#pragma once

#ifndef BILLBOARD_SPRITE_H
#define BILLBOARD_SPRITE_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>

enum BILLBOARD_RENDER_MODE {
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

    bool playing;

    int frameSpeedCount; 
    int loopCount;
    void drawBillboardTexture(raylib::Texture2D* atlasTexture);
public:
    // <Animation Name>
    sl::Signal<std::string> animationStarted;
    // <Animation Name>
    sl::Signal<std::string> animationStopped;
    // <Animation Name, Frame Index, DeltaTime>
    sl::Signal<std::string, int, float> animationUpdating;
    // <Animation Name, Loops Left>
    sl::Signal<std::string, int> animationLooped;

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

    void update(float dT) override;
    void render() override;
};

#endif