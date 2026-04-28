#include <engine/assets/texture_asset_loader.h>

TextureAssetLoader::TextureAssetLoader()
{
    this->jsonReader = new JSONHandler();
    this->assetCache = std::map<std::string, raylib::Texture2D*>{};
    this->textureAtlasCache = std::map<std::string, TextureAtlas*>{};
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
        json animationData = metaData.at("animations");

        raylib::Texture2D* foundTexture = new raylib::Texture2D(metaData.at("image"));

        TextureAtlas* newTextureAtlas = new TextureAtlas(id, foundTexture);

        for (auto& entry : frameData) {
            std::string frameName = entry.at("filename");
            json frame = entry.at("frame");

            newTextureAtlas->addFrame(frameName, raylib::Rectangle(frame.at("x"), frame.at("y"), frame.at("w"), frame.at("h")));
        }

        this->textureAtlasCache.insert({id, newTextureAtlas});
        // if (animationData) {
        //     for (auto& entry : animationData) {
        //         std::string animationName = entry.at("id");

        //         for (auto& frameName: entry.at("frames")) {
        //             this->animationCache.insert({animationName, frameName});
        //         }
        //     }
        // }
    }
}

void TextureAssetLoader::unloadCurrentManifest() {
    for (const auto& [key, value] : this->assetCache) {
        if (value->IsValid()) {
            ::UnloadTexture(*value);
        }
    }

    this->assetCache = std::map<std::string, raylib::Texture2D*>{};
    this->textureAtlasCache = std::map<std::string, TextureAtlas*>{};
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

TextureAtlas* TextureAssetLoader::getTextureAtlas(std::string atlasID) {
    auto it = this->textureAtlasCache.find(atlasID);

    if (it == this->textureAtlasCache.end()) {
        // Element Not Found
        return nullptr;
    }

    auto textureAtlas = this->textureAtlasCache.at(atlasID);

    return textureAtlas;
}
