#pragma once

#ifndef STAGE_MANAGER_H
#define STAGE_MANAGER_H

#include <map>
#include <engine/screen/stage.h>
#include <engine/screen/scene.h>

class StageManager
{
private:
    std::map<std::string, Scene*> sceneMap;
    std::map<std::string, Stage*> stageMap;
public:
    StageManager();
    ~StageManager();

    void addScene(std::string id, Scene* scene);

    void createStage(std::string id, std::string initialScene);

    void changeScene(std::string stage, std::string newScene);

    bool updateStages(float dT);

    void renderStages();
};

#endif