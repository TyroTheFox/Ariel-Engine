#pragma once

#ifndef ANIMATED_SPRITE_CREATOR_H
#define ANIMATED_SPRITE_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/assets/texture_asset_loader.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/2D/animated_sprite.h>

class AnimatedSpriteCreator : public BaseCreator {
    private:
    public:
        AnimatedSpriteCreator();
        ~AnimatedSpriteCreator();

        AnimatedSprite* createActor(json* actorData) const;
};

#endif