#pragma once

#include <string>
#include <mutex>
#include <map>
#include "engine/utility/json_reader.h"
#include "raylib.h"

class TextureAssetLoader
{
    private:
        JSONReader *jsonReader;
        std::map<std::string, Texture2D> assetCache;
    public:
        TextureAssetLoader()
        {
            this->jsonReader = new JSONReader();
            this->assetCache = std::map<std::string, Texture2D>{};
        }

        ~TextureAssetLoader()
        {
            // When destroyed, unload all textures
            for (const auto& [key, value] : this->assetCache) {
                UnloadTexture(value);
            }

            this->assetCache = std::map<std::string, Texture2D>{};
        }

        void loadManifest(std::string path) {
            const rapidjson::Document jsonData = this->jsonReader->readJSON(path);
            const rapidjson::GenericArray<true, rapidjson::Value> manifest = jsonData["manifest"].GetArray();

            for (rapidjson::Value::ConstValueIterator itr = manifest.Begin(); itr != manifest.End(); ++itr) {
                const char *id = itr['id'].GetString();
                const char *src = itr['src'].GetString();

                const Texture2D foundTexture = LoadTexture(src);

                this->assetCache.insert({id, foundTexture});
            }
        }

        void unloadCurrentManifest() {
            for (const auto& [key, value] : this->assetCache) {
                UnloadTexture(value);
            }

            this->assetCache = std::map<std::string, Texture2D>{};
        }

        Texture2D getTexture(std::string textureID) {
            return this->assetCache.at(textureID);
        }
};
