#include <engine/game/game_instance.h>

GameInstance::GameInstance() {
}

GameInstance::~GameInstance() {
}

void GameInstance::instantiateGame(std::string assetManifestPath) {
    this->gameWindow = new raylib::Window(this->screenWidth, this->screenHeight, "Game", FLAG_VSYNC_HINT);

    Ariel::Global::assetLoader.loadManifest(assetManifestPath);
}

void GameInstance::startGame() {
    this->gameWindow->SetTargetFPS(this->targetFPS);

    RenderTexture2D renderTexture = LoadRenderTexture(this->screenWidth, this->screenHeight);

    while (!this->gameWindow->ShouldClose()) {
        float dT = this->gameWindow->GetFrameTime();

        // Update
        if (!Ariel::Global::stageManager.updateStages(dT)) {
            break;
        }
        
        // Render Screen
        BeginTextureMode(renderTexture);
            this->gameWindow->ClearBackground(raylib::Color::Black());
            Ariel::Global::stageManager.renderStages();
        EndTextureMode();


        // Draw
        BeginDrawing();
            DrawTexturePro(
                renderTexture.texture,
                Rectangle{ 0, 0, static_cast<float>(renderTexture.texture.width), static_cast<float>(-renderTexture.texture.height) },
                Rectangle{ 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
                Vector2{ 0, 0 },
                0,
                WHITE
            );
        EndDrawing();
    }

     UnloadRenderTexture(renderTexture);
}