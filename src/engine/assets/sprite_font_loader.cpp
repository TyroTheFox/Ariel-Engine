#include "engine/assets/sprite_font_loader.h"

std::map<std::string, raylib::Font> SpriteFontLoader::fontCache{};

SpriteFontLoader::SpriteFontLoader() {}

SpriteFontLoader::~SpriteFontLoader() {}

void SpriteFontLoader::loadManifest(json jsonData) {
    json manifest = jsonData.at("fonts");

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
            ::UnloadFont(value);
        }
    }

    this->fontCache = std::map<std::string, raylib::Font>{};
}

raylib::Font* SpriteFontLoader::getFontPtr(std::string fontID) {
    auto searchedFontCount = this->fontCache.count(fontID);

    if (searchedFontCount == 0) {
        // Element Not Found
        raylib::Font defaultFont = ::GetFontDefault();
        return &defaultFont;
    }

    auto fontPtr = &this->fontCache.at(fontID);

    return fontPtr;
}