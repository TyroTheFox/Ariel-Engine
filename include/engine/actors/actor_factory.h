#pragma once

#ifndef ACTOR_FACTORY_H
#define ACTOR_FACTORY_H

#include <map>
#include <nlohmann/json.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>

#include <engine/assets/texture_asset_loader.h>
#include <engine/assets/sprite_font_loader.h>

#include <engine/creators/2D/sprite_creator.h>
#include <engine/creators/2D/text_creator.h>
#include <engine/creators/2D/animated_sprite_creator.h>
#include <engine/creators/2D/shape_creator.h>

using json = nlohmann::json;

class ActorFactory {
private:
    JSONHandler *jsonReader;
    std::map<std::string, void*> actorCreators;
    TextureAssetLoader* textureAssetLoader; 
    SpriteFontLoader* spriteFontLoader;
public:
    ActorFactory(TextureAssetLoader* textureAssetLoaderPtr, SpriteFontLoader* spriteFontLoaderPtr);
    ~ActorFactory();

    void addNewCreator(std::string actorType, BaseCreator* creatorPtr);

    BaseActor* createActor(json* actorData);
};

#endif