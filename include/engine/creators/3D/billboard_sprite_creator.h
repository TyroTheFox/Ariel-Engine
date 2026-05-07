#pragma once

#ifndef BILLBOARD_SPRITE_CREATOR_H
#define BILLBOARD_SPRITE_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/3D/billboard_sprite.h>

class BillboardSpriteCreator : public BaseCreator {
    private:
    public:
        BillboardSpriteCreator();
        ~BillboardSpriteCreator();

        BillboardSprite* createActor(json* actorData) const;
};

#endif