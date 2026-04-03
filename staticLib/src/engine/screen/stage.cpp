#pragma once

#include <iostream>
#include <typeinfo>
#include <map>

#include "engine/actors/base_actor.h"
#include "scene.cpp"

class Stage
{
    protected:
        Scene* currentScene = nullptr;
    public:
        std::string id = "";

        Stage() {
            this->id = "Stage";
        }

        Stage(std::string id, Scene* scene) {
            this->id = id;
            this->transitionTo(scene);
        }

        ~Stage() {
            delete this->currentScene;
        }

        void transitionTo(Scene* scene) {
            std::cout << "Context: Transition to " << typeid(*scene).name() << ".\n";

            this->currentScene->onExit();

            if (this->currentScene != nullptr)
                delete this->currentScene;

            this->currentScene = scene;
            this->currentScene->set_stage(this);

            this->currentScene->onInit();
            this->currentScene->onEnter();
        }

        void updateScene(float dT) {
            if (this->currentScene == nullptr) {
                return;
            }

            this->currentScene->onUpdate(dT);
        }

        void renderScene() {
            if (this->currentScene == nullptr) {
                return;
            }

            this->currentScene->onRender();
        }
};