#pragma once

#ifndef SHAPE_MESH_CREATOR_H
#define SHAPE_MESH_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/3D/shape_mesh.h>
#include <engine/utility/convert_text_to_colour.h>

class ShapeMeshCreator : public BaseCreator {
private:
public:
    ShapeMeshCreator(/* args */);
    ~ShapeMeshCreator();

    ShapeMesh* createActor(json* actorData) const;
};

#endif