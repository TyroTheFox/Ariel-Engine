/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <string>

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "engine/utility/json_handler.h"
#include "engine/game/game_instance.h"

#include "scenes/test_scene.h"

const std::string assetManifestPath = "resources/data/asset_manifest.json";

int main () {
	JSONHandler jsonHandler = JSONHandler();
    GameInstance gameInstance = GameInstance();

    gameInstance.instantiateGame(assetManifestPath);

    json testSceneData = jsonHandler.readJSON("resources/data/scenes/test_scene.json");
    TestScene* testScene = new TestScene("test", testSceneData, gameInstance.actorFactory);

    gameInstance.stageManager->addScene("test", testScene);

    gameInstance.stageManager->createStage("main", "test");

    gameInstance.startGame();
	return 0;
}
