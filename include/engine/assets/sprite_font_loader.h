#pragma once

#include "raylib.h"

#include <engine/utility/json_handler.h>

class SpriteFontLoader
{
private:
    JSONHandler jsonHandler;
    std::map<std::string, Font> fontCache;
public:
    SpriteFontLoader();
    ~SpriteFontLoader();

    void loadManifest(std::string path);
    void unloadCurrentManifest();
    Font getFont(std::string fontID);
    Font* getFontPtr(std::string fontID);
};

