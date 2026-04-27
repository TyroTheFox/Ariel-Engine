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

using json = nlohmann::json;

class TextureAssetLoader
{
    private:
        JSONHandler *jsonReader;
        // ID, Texture
        std::map<std::string, raylib::Texture2D*> assetCache;
        // ID, <Frame Rectangle, Atlas Texture ID (from Asset Cache)>
        std::map<std::string, std::tuple<raylib::Rectangle, std::string>> atlasFrameCache;
        std::string defaultResourcePath;
    public:
        TextureAssetLoader();
        ~TextureAssetLoader();

        json loadJSONAsDocument(std::string path);

        void loadManifest(std::string path);

        void unloadCurrentManifest();

        raylib::Texture2D* getTexturePtr(std::string textureID);

        std::tuple<raylib::Rectangle, std::string>* getFrameData(std::string atlasID);
};

#endif