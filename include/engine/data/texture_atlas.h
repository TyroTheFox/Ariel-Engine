#pragma once

#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <string>
#include <vector>
#include <map>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

struct AtlasFrame {
    std::string id;
    raylib::Rectangle frameRect;
    bool rotated;
};

struct SpriteAnimation {
    std::string id;
    std::vector<std::string> frames;
    float playSpeed;
    int loopCount;
};

class TextureAtlas {
private:
    std::string id;
    std::vector<AtlasFrame> frames;
    raylib::Texture2D* atlasTexture;
    std::map<std::string, SpriteAnimation*> animationMap;
    float scale;
public:
    TextureAtlas(std::string id, raylib::Texture2D* atlasTexture, float scale = 1.0F);
    ~TextureAtlas();

    float getTextureScale();

    void addFrame(std::string id, raylib::Rectangle frameRect, bool rotated = false);
    raylib::Rectangle getFrameRect(std::string frameID);
    bool getFrameRotated(std::string frameID);
    void setAtlasTexture(raylib::Texture2D* texturePtr);
    raylib::Texture2D* getAtlasTexture();
    std::vector<AtlasFrame> getFrameList();
    void addAnimation(std::string key, std::vector<std::string> frameList, int playSpeed = 12, int loopCount = 0);
    SpriteAnimation* getAnimation(std::string animationId);
    bool atlasTextureIsValid();
};

#endif