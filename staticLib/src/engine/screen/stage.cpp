#include <iostream>
#include <typeinfo>
#include <map>

#include "engine/actors/base_actor.h"
#include "scene.cpp"

class Stage
{
private:
    std::string id = "";
    Scene* currentScene = nullptr;
public:
    sl::Signal<> onInit;
    sl::Signal<> onEnter;
    sl::Signal<float dT> onUpdate;
    sl::Signal<> onRender;
    sl::Signal<> onExit;

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
};