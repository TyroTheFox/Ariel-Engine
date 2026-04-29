#pragma once

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <string>
#include <vector>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>

class AnimatedSprite: public BaseActor {
private:
    TextureAtlas* textureAtlas;

    std::string currentFrameID;
    std::string defaultFrameID;
    int currentFrameIndex;

    std::string currentAnimation;

    bool playing;

    float frameSpeed;
    int frameSpeedCount; 

    int loopCount = -1;
public:
    AnimatedSprite(std::string id, TextureAtlas* textureAtlas, std::string defaultFrame = "default");
    ~AnimatedSprite();

    void setTextureAtlas(TextureAtlas* textureAtlas);

    void playAnimation(std::string animationID);
    void stopAnimation();

    void setFrameSpeed(int speed);
    void setLoopCount(int loop);

    void update(float dT) override;
    void render() override;
};

#endif