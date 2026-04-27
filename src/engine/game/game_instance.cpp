#include <engine/game/game_instance.h>

GameInstance::GameInstance() {
    this->textureAssetLoader = new TextureAssetLoader();
    this->spriteFontLoader = new SpriteFontLoader();
    
    this->actorFactory = new ActorFactory(this->textureAssetLoader, this->spriteFontLoader);
    this->stageManager = new StageManager(this->actorFactory);
}

GameInstance::~GameInstance() {
    delete this->actorFactory;
    delete this->stageManager;
    delete this->textureAssetLoader;
}

void GameInstance::instantiateGame(std::string assetManifestPath) {
    this->gameWindow = new raylib::Window(this->screenWidth, this->screenHeight, "Game", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    this->textureAssetLoader->loadManifest(assetManifestPath);
}

void GameInstance::startGame() {
    this->gameWindow->SetTargetFPS(this->targetFPS);

    while (!this->gameWindow->ShouldClose()) {
        float dT = this->gameWindow->GetFrameTime();

        // Update
        if (!this->stageManager->updateStages(dT)) {
            break;
        }

        // Draw
        // this->gameWindow.BeginDrawing();
        BeginDrawing();

            this->gameWindow->ClearBackground(raylib::Color::Black());
            // ClearBackground(raylib::Color(0, 0, 0, 255));

            this->stageManager->renderStages();

        // this->gameWindow.EndDrawing();
        EndDrawing();
    }
}