#pragma once

#ifndef SHAPE_CREATOR_H
#define SHAPE_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/creators/base_creator.h>
#include <engine/actors/2D/shape.h>

class ShapeCreator : public BaseCreator {
private:
public:
    ShapeCreator();
    ~ShapeCreator();

    Shape* createActor(json* actorData) const;
};

#endif