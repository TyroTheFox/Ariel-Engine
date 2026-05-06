#pragma once

#ifndef ACTOR_FACTORY_H
#define ACTOR_FACTORY_H

#include <map>
#include <nlohmann/json.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>

#include <engine/assets/asset_loader.h>

#include <engine/creators/2D/sprite_creator.h>
#include <engine/creators/2D/text_creator.h>
#include <engine/creators/2D/animated_sprite_creator.h>
#include <engine/creators/2D/shape_creator.h>

#include <engine/creators/3D/mesh_creator.h>
#include <engine/creators/3D/shape_mesh_creator.h>

using json = nlohmann::json;

class ActorFactory {
private:
    JSONHandler *jsonReader;
    std::map<std::string, void*> actorCreators;
    AssetLoader* assetLoader;
public:
    ActorFactory(AssetLoader* assetLoaderPtr);
    ~ActorFactory();

    void addNewCreator(std::string actorType, BaseCreator* creatorPtr);

    BaseActor* createActor(json* actorData);
};

#endif