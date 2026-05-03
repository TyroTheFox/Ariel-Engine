#pragma once

#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

#include <map>
#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/assets/asset_loader.h>

#include <engine/screen/stage_manager.h>
#include <engine/actors/actor_factory.h>

class GameInstance {
    private:
        const int screenWidth = 1600;
        const int screenHeight = 900;
        const int targetFPS = 60;
    public:
        AssetLoader assetLoader;

        ActorFactory* actorFactory;
        StageManager* stageManager;

        raylib::Window* gameWindow;
        
        GameInstance();
        ~GameInstance();

        void instantiateGame(std::string assetManifestPath);
        void startGame();
};

#endif