#pragma once 

#include <map>
#include "engine/actors/base_actor.h"
#include "src/engine/screen/stage.cpp"
#include "src/engine/actors/container.cpp"

class Scene
{
protected:
    Stage* currentStage = nullptr;
    std::map<std::string, BaseActor> children;
    Container* baseContainer;
public:
    std::string id = "";
    sl::Signal<> actorAdded;
    sl::Signal<> actorRemoved;

    sl::Signal<float> onUpdate;
    sl::Signal<> onRender;

    Scene() {
        this->id = "Scene";
        this->baseContainer = new Container(id + "_Container");
        this->children = std::map<std::string, BaseActor>{};
    }

    Scene(std::string id) {
        this->id = id;
        this->baseContainer = new Container(id + "_Container");
        this->children = std::map<std::string, BaseActor>{};
    }
    ~Scene();

    void addActor(BaseActor actor) {
        this->children.insert({actor.id, actor});
    }

    void set_stage(Stage *stage) {
        this->currentStage = stage;
    }

    virtual void onInit();
    virtual void onEnter();
    virtual void onExit();

    void onUpdate(float dT) {
        this->onUpdate.emit(dT);
    }

    void onRender() {
        this->onRender.emit();
    }
};
