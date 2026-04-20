#include <engine/screen/stage.h>

Stage::Stage() {
    this->id = "Stage";
    this->currentScene = nullptr;
}

Stage::Stage(std::string id, Scene* scene) {
    this->id = id;
    this->transitionTo(scene);
}

Stage::~Stage() {
    delete this->currentScene;
}

void Stage::transitionTo(Scene* scene) {
    std::cout << "Context: Transition to " << typeid(*scene).name() << ".\n";

    this->currentScene->onExit();

    if (this->currentScene != nullptr)
        delete this->currentScene;

    this->currentScene = scene;

    this->currentScene->onInit();
    this->currentScene->onEnter();
}

void Stage::updateScene(float dT) {
    if (this->currentScene == nullptr) {
        return;
    }

    this->currentScene->onUpdate(dT);
}

void Stage::renderScene() {
    if (this->currentScene == nullptr) {
        return;
    }

    this->currentScene->onRender();
}