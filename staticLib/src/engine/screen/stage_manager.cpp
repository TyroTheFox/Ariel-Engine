#pragma once

#include <map>
#include "src/engine/screen/stage.cpp"
#include "src/engine/screen/scene.cpp"

class StageManager
{
private:
    std::map<std::string, Scene*> sceneMap;
    std::map<std::string, Stage*> stageMap;
public:
    StageManager() {
        this->sceneMap = std::map<std::string, Scene*>{};
        this->stageMap = std::map<std::string, Stage*>{};
    }
    ~StageManager();

    void addScene(std::string id, Scene* scene) {
        this->sceneMap.insert({ id, scene });
    }

    void createStage(std::string id, std::string initialStage) {
        auto foundScene = this->sceneMap.find(initialStage);

        if (foundScene == this->sceneMap.end()) {
            return;
        }

        Stage* newStage = new Stage(id, foundScene->second);

        this->stageMap.insert({ id, newStage });
    }

    void changeScene(std::string stage, std::string newScene) {
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

    bool updateStages(float dT) {
        std::map<std::string, Stage*>::iterator it;

        for (it = this->stageMap.begin(); it != this->stageMap.end(); it++)
        {
            it->second->updateScene(dT);
        }

        return true;
    }

    void renderStages() {
        std::map<std::string, Stage*>::iterator it;

        for (it = this->stageMap.begin(); it != this->stageMap.end(); it++)
        {
            it->second->renderScene();
        }
    }
};
