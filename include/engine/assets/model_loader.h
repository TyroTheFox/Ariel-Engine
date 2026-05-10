#pragma once

#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <string>
#include <mutex>
#include <map>
#include <memory>
#include <tuple>
#include <nlohmann/json.hpp>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>

class ModelLoader {
private:
    JSONHandler *jsonReader;
    // ID, Texture
    static std::map<std::string, raylib::Model*> assetCache;
public:
    ModelLoader();
    ~ModelLoader();

    void loadManifest(json jsonData);

    void unloadCurrentManifest();

    raylib::Model* getModelPtr(std::string modelID);
};

#endif