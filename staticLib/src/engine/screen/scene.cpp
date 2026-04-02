#include <map>
#include "engine/actors/base_actor.h"
#include "stage.cpp"

class Scene
{
private:
    Stage* currentStage = nullptr;
    std::map<std::string, BaseActor> children;
public:
    sl::Signal<> actorAdded;
    sl::Signal<> actorRemoved;

    sl::Signal<float dT> onUpdate;
    sl::Signal<> onRender;

    Scene();
    ~Scene();

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
