#pragma once

#ifndef STAGE_H
#define STAGE_H

#include <iostream>
#include <typeinfo>
#include <map>

#include <engine/actors/base_actor.h>
#include <engine/screen/scene.h>

class Stage
{
    protected:
        Scene* currentScene;
    public:
        std::string id = "";

        Stage();

        Stage(std::string id, Scene* scene);

        ~Stage();
        
        void transitionTo(Scene* scene);
        void updateScene(float dT);
        void renderScene();
};

#endif