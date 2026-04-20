#include "scenes/test_scene.h"

TestScene::TestScene() : Scene() {
}

TestScene::TestScene(std::string id, json sceneData, ActorFactory* actorFactoryPtr) : Scene(id, sceneData, actorFactoryPtr) {
}