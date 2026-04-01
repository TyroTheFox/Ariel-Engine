#pragma once

#include <string>
#include <map>

#include "raylib.h"
#include "engine/actors/base_actor.h"

class Actor: public BaseActor
{
private:
    float x = 0;
    float y = 0;
    float pivotX = 0;
    float pivotY = 0;
    float scaleX = 0;
    float scaleY = 0;
    float rotation = 0;

    std::map<std::string, BaseActor> children;
public:
    Actor();
    ~Actor();
};