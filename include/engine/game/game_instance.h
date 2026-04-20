#pragma once

#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

#include <map>
#include <string>

#include <raylib.h>
#include <engine/assets/texture_asset_loader.h>
#include <engine/screen/stage_manager.h>
#include <engine/actors/actor_factory.h>

class GameInstance {
    private:
        const int screenWidth = 800;
        const int screenHeight = 450;
        const int targetFPS = 60;

    public:
        TextureAssetLoader* textureAssetLoader;
        ActorFactory* actorFactory;
        StageManager* stageManager;
        
        GameInstance();
        ~GameInstance();

        void instantiateGame(std::string assetManifestPath);
        void startGame();
};

#endif