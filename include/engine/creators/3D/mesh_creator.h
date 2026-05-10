#pragma once

#ifndef MESH_CREATOR_H
#define MESH_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/assets/model_loader.h>
#include <engine/assets/texture_asset_loader.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/3D/mesh.h>
#include <engine/utility/convert_text_to_colour.h>

class MeshCreator : public BaseCreator {
private:
    /* data */
public:
    MeshCreator(/* args */);
    ~MeshCreator();

    MeshModel* createActor(json* actorData) const;
};

#endif