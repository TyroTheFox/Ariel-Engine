#include <engine/assets/asset_loader.h>

AssetLoader::AssetLoader() {
    this->jsonReader = JSONHandler();
    this->textureAssetLoader =  new TextureAssetLoader();
    this->spriteFontLoader = new SpriteFontLoader();
    this->modelLoader = new ModelLoader();
}

AssetLoader::~AssetLoader() {
}

json AssetLoader::loadJSONAsDocument(std::string path) {
    return this->jsonReader.readJSON(path);
}

void AssetLoader::loadManifest(std::string path) {
    json jsonData = this->jsonReader.readJSON(path);

    this->textureAssetLoader->loadManifest(jsonData);

    this->spriteFontLoader->loadManifest(jsonData);

    this->modelLoader->loadManifest(jsonData);
}

raylib::Texture2D* AssetLoader::getTexturePtr(std::string textureID) {
    return this->textureAssetLoader->getTexturePtr(textureID);
}

TextureAtlas* AssetLoader::getTextureAtlas(std::string atlasID) {
    return this->textureAssetLoader->getTextureAtlas(atlasID);
}

raylib::Font* AssetLoader::getFontPtr(std::string fontID) {
    return this->spriteFontLoader->getFontPtr(fontID);
}

raylib::Model* AssetLoader::getModelPtr(std::string modelID) {
    return this->modelLoader->getModelPtr(modelID);
}