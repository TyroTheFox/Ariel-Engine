#include <engine/game/game_instance.h>

GameInstance::GameInstance() {
    this->assetLoader = AssetLoader();
    
    this->actorFactory = new ActorFactory(&this->assetLoader);
    this->stageManager = new StageManager(this->actorFactory);
}

GameInstance::~GameInstance() {
    delete this->actorFactory;
    delete this->stageManager;
}

void GameInstance::instantiateGame(std::string assetManifestPath) {
    this->gameWindow = new raylib::Window(this->screenWidth, this->screenHeight, "Game", FLAG_VSYNC_HINT);

    this->assetLoader.loadManifest(assetManifestPath);
}

void GameInstance::startGame() {
    this->gameWindow->SetTargetFPS(this->targetFPS);

    RenderTexture2D renderTexture = LoadRenderTexture(this->screenWidth, this->screenHeight);

    while (!this->gameWindow->ShouldClose()) {
        float dT = this->gameWindow->GetFrameTime();

        // Update
        if (!this->stageManager->updateStages(dT)) {
            break;
        }
        
        // Render Screen
        BeginTextureMode(renderTexture);
            this->gameWindow->ClearBackground(raylib::Color::Black());
            this->stageManager->renderStages();
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