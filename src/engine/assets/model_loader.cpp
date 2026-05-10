#include <engine/assets/model_loader.h>

std::map<std::string, raylib::Model*> ModelLoader::assetCache{};

ModelLoader::ModelLoader() {}

ModelLoader::~ModelLoader() {}

void ModelLoader::loadManifest(json jsonData) {
    json modelManifest = jsonData.at("models");

    for (auto& entry : modelManifest) {
        std::string src = entry.at("src");
        std::string id = entry.at("id");

        raylib::Model* foundModel = new raylib::Model(src);

        this->assetCache.insert({id, foundModel});
    }
}

void ModelLoader::unloadCurrentManifest() {
    for (const auto& [key, value] : this->assetCache) {
        if (value->IsValid()) {
            ::UnloadModel(*value);
        }
    }

    this->assetCache = std::map<std::string, raylib::Model*>{};
}

raylib::Model* ModelLoader::getModelPtr(std::string modelID) {
    auto it = this->assetCache.find(modelID);

    if (it == this->assetCache.end()) {
        // Element Not Found
        return nullptr;
    }

    auto modelPtr = this->assetCache.at(modelID);

    return modelPtr;
}