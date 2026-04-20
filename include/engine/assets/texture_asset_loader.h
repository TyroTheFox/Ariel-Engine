#pragma once

#ifndef TEXTURE_ASSET_LOADER_H
#define TEXTURE_ASSET_LOADER_H

#include <string>
#include <mutex>
#include <map>
#include <nlohmann/json.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>

using json = nlohmann::json;

class TextureAssetLoader
{
    private:
        JSONHandler *jsonReader;
        std::map<std::string, Texture2D*> assetCache;
    public:
        TextureAssetLoader();
        ~TextureAssetLoader();

        json loadJSONAsDocument(std::string path);

        void loadManifest(std::string path);

        void unloadCurrentManifest();

        Texture2D getTexture(std::string textureID);

        Texture2D* getTexturePtr(std::string textureID);
};

#endif