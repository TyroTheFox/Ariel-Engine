#pragma once

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <string>
#include <vector>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>

class AnimatedSprite: public BaseActor {
private:
    raylib::Texture2D* texture;
    std::map<std::string, raylib::Rectangle> frameMap;
    std::map<std::string, std::vector<std::string>> animationMap;

    std::string currentFrameID;
    int currentFrameIndex;

    std::string currentAnimation;

    bool playing;

    float frameSpeed;
    float frameSpeedCount; 

    int loopCount = -1;
public:
    AnimatedSprite(std::string id, raylib::Texture2D* atlasTexture);
    ~AnimatedSprite();

    void setTexture(raylib::Texture2D* texturePtr);
    void setFrame(std::string frameName);
    void addFrame(std::string frameID, raylib::Rectangle frameRect);
    void addAnimation(std::string animationId, std::vector<std::string> animationFrames);

    void playAnimation(std::string animationID);
    void stopAnimation();

    void setFrameSpeed(int speed);
    void setLoopCount(int loop);

    void update(float dT) override;
    void render() override;
};

#endif