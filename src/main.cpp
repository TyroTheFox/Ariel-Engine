/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <string>

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "engine/globals.h"

#include "engine/utility/json_handler.h"

#include "scenes/test_scene.h"

const std::string assetManifestPath = "resources/data/asset_manifest.json";

int main () {
	JSONHandler jsonHandler = JSONHandler();

    Ariel::Global::gameInstance.instantiateGame(assetManifestPath);

    json testSceneData = jsonHandler.readJSON("resources/data/scenes/test_scene.json");
    TestScene* testScene = new TestScene("test", testSceneData);

    Ariel::Global::stageManager.addScene("test", testScene);

    Ariel::Global::stageManager.createStage("main", "test");

    Ariel::Global::gameInstance.startGame();
	return 0;
}
