#pragma once

#ifndef SPRITE_CREATOR_H
#define SPRITE_CREATOR_H

#include <raylib.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/2D/sprite.h>

class SpriteCreator: public BaseCreator {
private:
    /* data */
public:
    SpriteCreator();
    ~SpriteCreator();

    Sprite* createActor(json* actorData) const;
};

#endif
