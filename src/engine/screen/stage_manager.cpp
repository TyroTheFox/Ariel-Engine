#include <engine/screen/stage_manager.h>

std::map<std::string, Scene*> StageManager::sceneMap{};
std::map<std::string, Stage*> StageManager::stageMap{};

StageManager::StageManager() {}

StageManager::~StageManager() {}

void StageManager::addScene(std::string id, Scene* scene) {
    this->sceneMap.insert({ id, scene });
}

void StageManager::createStage(std::string id, std::string initialScene) {
    auto foundScene = this->sceneMap.find(initialScene);

    if (foundScene == this->sceneMap.end()) {
        return;
    }

    Stage* newStage = new Stage(id, foundScene->second);

    this->stageMap.insert({ id, newStage });
}

void StageManager::changeScene(std::string stage, std::string newScene) {
    std::map<std::string, Stage*>::iterator foundStage = this->stageMap.find(stage);

    if (foundStage == this->stageMap.end()) {
        return;
    }

    std::map<std::string, Scene*>::iterator foundScene = this->sceneMap.find(newScene);

    if (foundScene == this->sceneMap.end()) {
        return;
    }
        
    foundStage->second->transitionTo(foundScene->second);
}

bool StageManager::updateStages(float dT) {
    std::map<std::string, Stage*>::iterator it;

    for (it = this->stageMap.begin(); it != this->stageMap.end(); it++)
    {
        it->second->updateScene(dT);
    }

    return true;
}

void StageManager::renderStages() {
    std::map<std::string, Stage*>::iterator it;

    for (it = this->stageMap.begin(); it != this->stageMap.end(); it++)
    {
        it->second->renderScene();
    }
}