#pragma once

#ifndef BILLBOARD_SPRITE_H
#define BILLBOARD_SPRITE_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>

class BillboardSprite : public BaseActor {
private:
    TextureAtlas* textureAtlas;

    std::string currentFrameID;
    std::string defaultAnimationID;
    int currentFrameIndex;

    SpriteAnimation* currentAnimation;

    bool playing;

    int frameSpeedCount; 
    int loopCount;
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

    void setTextureAtlas(TextureAtlas* textureAtlas);

    void setSceneCamera(raylib::Camera3D* camera);

    void playAnimation(std::string animationID);
    void stopAnimation();

    void update(float dT) override;
    void render() override;
};

#endif