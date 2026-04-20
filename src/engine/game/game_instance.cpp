#include <engine/game/game_instance.h>

GameInstance::GameInstance() {
    this->textureAssetLoader = new TextureAssetLoader();
    this->actorFactory = new ActorFactory(this->textureAssetLoader);
    this->stageManager = new StageManager(this->actorFactory);

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
}

GameInstance::~GameInstance() {
    delete this->actorFactory;
    delete this->stageManager;
    delete this->textureAssetLoader;
}

void GameInstance::instantiateGame(std::string assetManifestPath) {
    InitWindow(this->screenWidth, this->screenHeight, "Game");
    SetTargetFPS(this->targetFPS);

    this->textureAssetLoader->loadManifest(assetManifestPath);
}

void GameInstance::startGame() {
    while (!WindowShouldClose()) {
        float dT = GetFrameTime();

        // Update
        if (!this->stageManager->updateStages(dT)) {
            break;
        }

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);

            this->stageManager->renderStages();

        EndDrawing();
    }

    CloseWindow();
}