#pragma once

#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include <string>
#include <map>
#include <memory>
#include <tuple>
#include <nlohmann/json.hpp>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>
#include <engine/data/texture_atlas.h>

#include <engine/assets/texture_asset_loader.h>
#include <engine/assets/sprite_font_loader.h>
#include <engine/assets/model_loader.h>

class AssetLoader {
private:
    JSONHandler jsonReader;
    std::string defaultResourcePath;

    TextureAssetLoader textureAssetLoader;
    SpriteFontLoader spriteFontLoader;
    ModelLoader modelLoader;
public:
    AssetLoader();
    ~AssetLoader();
    
    json loadJSONAsDocument(std::string path);
    void loadManifest(std::string path);

    raylib::Texture2D* getTexturePtr(std::string textureID);
    TextureAtlas* getTextureAtlas(std::string atlasID);

    raylib::Font* getFontPtr(std::string fontID);

    raylib::Model* getModelPtr(std::string modelID);
};

#endif