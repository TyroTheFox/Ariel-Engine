#include "engine/assets/sprite_font_loader.h"

SpriteFontLoader::SpriteFontLoader() {
    this->jsonHandler = JSONHandler();
    this->fontCache = std::map<std::string, Font>{};
}

SpriteFontLoader::~SpriteFontLoader() {
    // When destroyed, unload all textures
    for (const auto& [key, value] : this->fontCache) {
        if (IsFontValid(value)) {
            UnloadFont(value);
        }
    }
}

void SpriteFontLoader::loadManifest(std::string path) {
    json jsonData = this->jsonHandler.readJSON(path);
    json manifest = jsonData.at("manifest");

    for (auto& entry : manifest) {
        std::string src = entry.at("src");
        std::string id = entry.at("id");

        Font foundFont = LoadFont(src.c_str());

        this->fontCache.insert({id, foundFont});
    }
}

void SpriteFontLoader::unloadCurrentManifest() {
    for (const auto& [key, value] : this->fontCache) {
        if (IsFontValid(value)) {
            UnloadFont(value);
        }
    }

    this->fontCache = std::map<std::string, Font>{};
}

Font SpriteFontLoader::getFont(std::string fontID) {
    return this->fontCache.at(fontID);
}

Font* SpriteFontLoader::getFontPtr(std::string fontID) {
    auto it = this->fontCache.find(fontID);

    if (it == this->fontCache.end()) {
        // Element Not Found
        return nullptr;
    }

    auto texturePtr = &this->fontCache.at(fontID);

    return texturePtr;
}