#include <engine/assets/texture_asset_loader.h>

TextureAssetLoader::TextureAssetLoader()
{
    this->jsonReader = new JSONHandler();
    this->assetCache = std::map<std::string, Texture2D>{};
}

TextureAssetLoader::~TextureAssetLoader()
{
    // When destroyed, unload all textures
    for (const auto& [key, value] : this->assetCache) {
        if (IsTextureValid(value)) {
            UnloadTexture(value);
        }
    }
}

json TextureAssetLoader::loadJSONAsDocument(std::string path) {
    return this->jsonReader->readJSON(path);
}

void TextureAssetLoader::loadManifest(std::string path) {
    json jsonData = this->jsonReader->readJSON(path);
    json manifest = jsonData.at("manifest");

    for (auto& entry : manifest) {
        std::string src = entry.at("src");
        std::string id = entry.at("id");

        Texture2D foundTexture = LoadTexture(src.c_str());

        this->assetCache.insert({id, foundTexture});
    }
}

void TextureAssetLoader::unloadCurrentManifest() {
    for (const auto& [key, value] : this->assetCache) {
        if (IsTextureValid(value)) {
            UnloadTexture(value);
        }
    }

    this->assetCache = std::map<std::string, Texture2D>{};
}

Texture2D TextureAssetLoader::getTexture(std::string textureID) {
    return this->assetCache.at(textureID);
}

Texture2D* TextureAssetLoader::getTexturePtr(std::string textureID) {
    auto it = this->assetCache.find(textureID);

    if (it == this->assetCache.end()) {
        // Element Not Found
        return nullptr;
    }

    auto texturePtr = &this->assetCache.at(textureID);

    return texturePtr;
}