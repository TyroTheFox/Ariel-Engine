#pragma once

#include <string>
#include "raylib.h"

#include "engine/actors/actor.h"

class Sprite : public Actor
{
private:
    std::string textureID;
    Texture2D *texture;
public:
    Sprite(/* args */);
    ~Sprite();
};

Sprite::Sprite(/* args */)
{
}

Sprite::~Sprite()
{
}
