#pragma once

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <string>
#include <vector>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <sling.h>

#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>
#include <engine/render/rendering_shader.h>

class AnimatedSprite: public BaseActor {
private:
    TextureAtlas* textureAtlas;

    std::string currentFrameID;
    std::string defaultFrameID;
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

    AnimatedSprite(std::string id, TextureAtlas* textureAtlas, std::string defaultFrame = "default");
    ~AnimatedSprite();

    void setTextureAtlas(TextureAtlas* textureAtlas);

    void playAnimation(std::string animationID);
    void stopAnimation();

    void update(float dT) override;
    void render(RenderingShader* shader) override;
};

#endif