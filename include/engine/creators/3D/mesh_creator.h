#pragma once

#ifndef MESH_CREATOR_H
#define MESH_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/3D/mesh.h>

class MeshCreator : public BaseCreator {
private:
    /* data */
public:
    MeshCreator(/* args */);
    ~MeshCreator();

    MeshModel* createActor(json* actorData) const;
};

#endif