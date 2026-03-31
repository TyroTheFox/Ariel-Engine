#include "engine/assets/asset_loader.h";

AssetLoader::AssetLoader()
{
    this->jsonReader = new JSONReader();
    this->assetCache = std::map<std::string, Texture2D>{};
}

AssetLoader::~AssetLoader()
{
    // When destroyed, unload all textures
    for (const auto& [key, value] : this->assetCache) {
        UnloadTexture(value);
    }

    this->assetCache = std::map<std::string, Texture2D>{};
}

// Load all textures into cache from manifest
void AssetLoader::loadManifest(std::string path)
{
    const rapidjson::Document jsonData = this->jsonReader->readJSON(path);
    const rapidjson::GenericArray<true, rapidjson::Value> manifest = jsonData["manifest"].GetArray();

    for (rapidjson::Value::ConstValueIterator itr = manifest.Begin(); itr != manifest.End(); ++itr) {
        const char *id = itr['id'].GetString();
        const char *src = itr['src'].GetString();

        const Texture2D foundTexture = LoadTexture(src);

        this->assetCache.insert({id, foundTexture});
    }
}

// Unload all currently loaded textures
void AssetLoader::unloadCurrentManifest() {
    for (const auto& [key, value] : this->assetCache) {
        UnloadTexture(value);
    }

    this->assetCache = std::map<std::string, Texture2D>{};
}