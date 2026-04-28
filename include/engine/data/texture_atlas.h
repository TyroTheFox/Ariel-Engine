#pragma once

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <string>
#include <vector>
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
public:
    TextureAtlas(std::string id, raylib::Texture2D* atlasTexture);
    ~TextureAtlas();

    void addFrame(std::string id, raylib::Rectangle frameRect);
    raylib::Rectangle getFrameRect(std::string frameID);
    raylib::Texture2D* getAtlasTexture();
    std::vector<AtlasFrame> getFrameList();
};

#endif