#pragma once

#include <map>
#include <string>

#include "raylib.h"
#include "src/engine/assets/texture_asset_loader.cpp"
#include "src/engine/screen/stage_manager.cpp"

#include "src/scenes/test_scene.cpp";

class GameInstance
{
private:
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int targetFPS = 60;

    TextureAssetLoader* textureAssetLoader;
    StageManager* stageManager;
public:
    GameInstance(){
        TestScene* testScene = new TestScene();

        this->textureAssetLoader = new TextureAssetLoader();
        this->stageManager = new StageManager();

        this->stageManager->addScene("test", testScene);

        this->stageManager->createStage("main", "test");

        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    }
    ~GameInstance();

    void startGame() {
        InitWindow(this->screenWidth, this->screenHeight, "Game");
        SetTargetFPS(this->targetFPS);

        while (!WindowShouldClose()) {
            float dT = GetFrameTime();

            // Update
            if (!this->stageManager->updateStages(dT)) {
                break;
            }

            // Draw
            BeginDrawing();

                ClearBackground(RAYWHITE);

                this->stageManager->renderStages();

            EndDrawing();
        }

        CloseWindow();
    }
};
