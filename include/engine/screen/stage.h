#pragma once

#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <typeinfo>
#include <map>

#include <engine/actors/base_actor.h>
#include <engine/screen/scene.h>
#include <engine/screen/stage_manager.h>

class Stage
{
    protected:
        Scene* currentScene;
        StageManager* attachedStageManager;
    public:
        std::string id = "";

        Stage(std::string id, Scene* scene, StageManager* stageManager);

        ~Stage();
        
        void transitionTo(Scene* scene);
        void updateScene(float dT);
        void renderScene();
};

#endif