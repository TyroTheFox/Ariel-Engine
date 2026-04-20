#include <engine/screen/scene.h>

Scene::Scene() {
    this->id = "scene";
    this->baseContainer = new Container("scene_Container");
    this->children = std::map<std::string, BaseActor*>{};
}

Scene::Scene(std::string name, json sceneData, ActorFactory* actorFactoryPtr) {
    this->id = name;
    this->baseContainer = new Container(name + "_Container");
    this->children = std::map<std::string, BaseActor*>{};

    this->actorFactory = actorFactoryPtr;

    this->settingsData = &sceneData.at("settings");
    this->actorData = &sceneData.at("actors");

    for (json entry : sceneData.at("actors")) {
        std::string actorId = entry.at("id");

        BaseActor* newActor = this->actorFactory->createActor(&entry);
        newActor->id = actorId;

        this->addActor(newActor);
    }
}

Scene::~Scene() {}

void Scene::addActor(BaseActor* actor) {
    this->children.insert({actor->id, actor});
    this->baseContainer->addChildren(actor);
    this->signal_update.connect(actor->onUpdate);
    this->signal_render.connect(actor->onRender);
}

void Scene::removeActor(std::string id) {
    BaseActor* actor = this->children.at(id);

    this->children.erase(id);
    this->baseContainer->removeChildren(id);
    this->signal_update.disconnect(actor->onUpdate);
    this->signal_render.disconnect(actor->onRender);
}

BaseActor* Scene::getActorByID(std::string id) {
    return this->children.at(id);
}

void Scene::onUpdate(float dT) {
    this->signal_update.emit(dT);
}

void Scene::onRender() {
    this->signal_render.emit();
}

void Scene::onInit() {}
void Scene::onEnter() {}
void Scene::onExit() {}
