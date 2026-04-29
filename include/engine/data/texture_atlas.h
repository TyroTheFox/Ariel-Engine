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
};

class TextureAtlas {
private:
    std::string id;
    std::vector<AtlasFrame> frames;
    raylib::Texture2D* atlasTexture;
    std::map<std::string, std::vector<std::string>> animationMap;
public:
    TextureAtlas(std::string id, raylib::Texture2D* atlasTexture);
    ~TextureAtlas();

    void addFrame(std::string id, raylib::Rectangle frameRect);
    raylib::Rectangle getFrameRect(std::string frameID);
    raylib::Texture2D* getAtlasTexture();
    std::vector<AtlasFrame> getFrameList();
    void addAnimation(std::string key, std::vector<std::string> frameList);
    std::vector<std::string> getAnimationFrames(std::string animationKey);
};

#endif