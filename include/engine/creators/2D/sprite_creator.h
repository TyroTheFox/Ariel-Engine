#pragma once

#ifndef SPRITE_CREATOR_H
#define SPRITE_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/assets/texture_asset_loader.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/2D/sprite.h>

class SpriteCreator: public BaseCreator {
public:
    SpriteCreator();
    ~SpriteCreator();

    Sprite* createActor(json* actorData) const;
};

#endif
