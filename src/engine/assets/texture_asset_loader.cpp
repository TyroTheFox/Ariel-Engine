#include <engine/assets/texture_asset_loader.h>

TextureAssetLoader::TextureAssetLoader()
{
    this->jsonReader = new JSONHandler();
    this->assetCache = std::map<std::string, raylib::Texture2D*>{};
    this->atlasFrameCache = std::map<std::string, std::tuple<raylib::Rectangle, std::string>>{};
}

TextureAssetLoader::~TextureAssetLoader()
{
    // When destroyed, unload all textures
    for (const auto& [key, value] : this->assetCache) {
        if (value->IsValid()) {
            ::UnloadTexture(*value);
        }
    }
}

json TextureAssetLoader::loadJSONAsDocument(std::string path) {
    return this->jsonReader->readJSON(path);
}

void TextureAssetLoader::loadManifest(std::string path) {
    json jsonData = this->jsonReader->readJSON(path);
    json textureManifest = jsonData.at("textures");
    json atlasManifest = jsonData.at("atlases");

    for (auto& entry : textureManifest) {
        std::string src = entry.at("src");
        std::string id = entry.at("id");

        raylib::Texture2D* foundTexture = new raylib::Texture2D(src);

        this->assetCache.insert({id, foundTexture});
    }

    for (auto& entry : atlasManifest) {
        std::string id = entry.at("id");
        std::string src = entry.at("src");

        json atlasData = this->jsonReader->readJSON(src);

        json metaData = atlasData.at("meta");
        json frameData = atlasData.at("frames");

        raylib::Texture2D* foundTexture = new raylib::Texture2D(metaData.at("image"));

        this->assetCache.insert({id, foundTexture});

        for (auto& entry : frameData) {
            std::string frameName = entry.at("filename");
            json frame = entry.at("frame");

            std::tuple<raylib::Rectangle, std::string> frameTuple(raylib::Rectangle(frame.at("x"), frame.at("y"), frame.at("w"), frame.at("h")), id);

            this->atlasFrameCache.insert({frameName, frameTuple});
        }
    }
}

void TextureAssetLoader::unloadCurrentManifest() {
    for (const auto& [key, value] : this->assetCache) {
        if (value->IsValid()) {
            ::UnloadTexture(*value);
        }
    }

    this->assetCache = std::map<std::string, raylib::Texture2D*>{};
    this->atlasFrameCache = std::map<std::string, std::tuple<raylib::Rectangle, std::string>>{};
}

raylib::Texture2D* TextureAssetLoader::getTexturePtr(std::string textureID) {
    auto it = this->assetCache.find(textureID);

    if (it == this->assetCache.end()) {
        // Element Not Found
        return nullptr;
    }

    auto texturePtr = this->assetCache.at(textureID);

    return texturePtr;
}

std::tuple<raylib::Rectangle, std::string>* TextureAssetLoader::getFrameData(std::string frameID) {
    auto it = this->atlasFrameCache.find(frameID);

    if (it == this->atlasFrameCache.end()) {
        // Element Not Found
        return nullptr;
    }

    auto frameTuple = this->atlasFrameCache.at(frameID);

    return &frameTuple;
}