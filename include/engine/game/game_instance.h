#pragma once

#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

#include <engine/global_values.h>

#include <map>
#include <string>

#include <nlohmann/json.hpp>

#include <engine/assets/texture_asset_loader.h>
#include <engine/assets/model_loader.h>
#include <engine/assets/sprite_font_loader.h>
#include <engine/render/shader_objects/shader_manager.h>

#include <engine/screen/stage_manager.h>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

using json = nlohmann::json;

class GameInstance {
    private:
        RenderingShader* postProcessingShader;
    public:
        raylib::Window* gameWindow;
        
        GameInstance();
        ~GameInstance();

        void instantiateGame(std::string assetManifestPath);
        void startGame();
};

#endif