#pragma once

#ifndef SPRITE_FONT_LOADER_H
#define SPRITE_FONT_LOADER_H

#include <raylibcpp/raylib-cpp.hpp>
#include "raylib.h"

#include <engine/utility/json_handler.h>

class SpriteFontLoader
{
private:
    static std::map<std::string, raylib::Font> fontCache;
public:
    SpriteFontLoader();
    ~SpriteFontLoader();

    void loadManifest(json jsonData);
    void unloadCurrentManifest();
    raylib::Font* getFontPtr(std::string fontID);
};

#endif