#pragma once

#ifndef TEXTURE_ASSET_LOADER_H
#define TEXTURE_ASSET_LOADER_H

#include <string>
#include <mutex>
#include <map>
#include <memory>
#include <tuple>
#include <nlohmann/json.hpp>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>
#include <engine/data/texture_atlas.h>

using json = nlohmann::json;

class TextureAssetLoader
{
    private:
        JSONHandler *jsonReader;
        // ID, Texture
        std::map<std::string, raylib::Texture2D*> assetCache;
        std::map<std::string, TextureAtlas*> textureAtlasCache;
        std::string defaultResourcePath;
    public:
        TextureAssetLoader();
        ~TextureAssetLoader();

        void loadManifest(json jsonData);

        void unloadCurrentManifest();

        raylib::Texture2D* getTexturePtr(std::string textureID);

        TextureAtlas* getTextureAtlas(std::string atlasID);
};

#endif