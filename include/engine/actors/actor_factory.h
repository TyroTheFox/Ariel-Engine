#pragma once

#ifndef ACTOR_FACTORY_H
#define ACTOR_FACTORY_H

#include <map>
#include <nlohmann/json.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>

#include <engine/creators/2D/sprite_creator.h>
#include <engine/assets/texture_asset_loader.h>

using json = nlohmann::json;

class ActorFactory {
private:
    JSONHandler *jsonReader;
    std::map<std::string, void*> actorCreators;
public:
    ActorFactory(TextureAssetLoader* textureAssetLoaderPtr);
    ~ActorFactory();

    BaseActor* createActor(json* actorData);
};

#endif