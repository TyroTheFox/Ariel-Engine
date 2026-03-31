#pragma once

#include <string>
#include <mutex>
#include <map>
#include "engine/utility/json_reader.h"
#include "raylib.h"

class AssetLoader
{
    private:
        /* data */
        JSONReader *jsonReader;
        std::map<std::string, Texture2D> assetCache;
    public:
        AssetLoader(/* args */);
        ~AssetLoader();

        void loadManifest(std::string path);
        void unloadCurrentManifest();
};