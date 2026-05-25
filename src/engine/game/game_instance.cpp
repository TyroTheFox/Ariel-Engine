#include <engine/game/game_instance.h>

GameInstance::GameInstance() {}

GameInstance::~GameInstance() {
    delete this->gameWindow;
}

void GameInstance::instantiateGame(std::string assetManifestPath) {
    JSONHandler jsonHandler = JSONHandler();

    TextureAssetLoader textureAssetLoader = TextureAssetLoader();
    SpriteFontLoader spriteFontLoader = SpriteFontLoader();
    ModelLoader modelLoader = ModelLoader();
    ShaderManager shaderManager = ShaderManager();

    this->gameWindow = new raylib::Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Game", FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);

    json jsonData = jsonHandler.readJSON(assetManifestPath);

    shaderManager.loadManifest(jsonData);

    textureAssetLoader.loadManifest(jsonData);

    spriteFontLoader.loadManifest(jsonData);

    modelLoader.loadManifest(jsonData);

    this->postProcessingShader = shaderManager.getShaderPtr("bloom");
}

void GameInstance::startGame() {
    StageManager stageManager = StageManager();

    this->gameWindow->SetTargetFPS(TARGET_FPS);

    RenderTexture2D renderTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!this->gameWindow->ShouldClose()) {
        float dT = this->gameWindow->GetFrameTime();

        // Update
        if (!stageManager.updateStages(dT)) {
            break;
        }
        
        // Render Screen
        ::BeginTextureMode(renderTexture);
            this->gameWindow->ClearBackground(raylib::Color::Black());
            stageManager.renderStages();
        ::EndTextureMode();
 
        // Draw
        ::BeginDrawing();
            this->postProcessingShader->shaderInstance.BeginMode();
                ::DrawTextureRec(
                    renderTexture.texture,
                    raylib::Rectangle{ 0, 0, static_cast<float>(renderTexture.texture.width), static_cast<float>(-renderTexture.texture.height) },
                    raylib::Vector2{ static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
                    WHITE
                );
            this->postProcessingShader->shaderInstance.EndMode();
        ::EndDrawing();
    }

    UnloadRenderTexture(renderTexture);
}