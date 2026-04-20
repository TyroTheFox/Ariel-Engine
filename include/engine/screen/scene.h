#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <nlohmann/json.hpp>

#include <engine/actors/base_actor.h>
#include <engine/actors/actor_factory.h>
#include <engine/actors/container.h>

using json = nlohmann::json;

class Scene
{
    protected:
        ActorFactory* actorFactory;

        std::map<std::string, BaseActor*> children;
        Container* baseContainer;
    public:
        json* settingsData;
        json* actorData;

        std::string id = "";
        sl::Signal<> actorAdded;
        sl::Signal<> actorRemoved;

        sl::Signal<float> signal_update;
        sl::Signal<> signal_render;

        Scene();
        Scene(std::string id, json sceneData, ActorFactory* actorFactoryPtr);
        ~Scene();

        void addActor(BaseActor* actor);
        void removeActor(std::string id);
        BaseActor* getActorByID(std::string id);

        virtual void onInit();
        virtual void onEnter();
        virtual void onExit();

        void onUpdate(float dT);
        void onRender();
};

#endif