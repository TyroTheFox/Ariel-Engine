#pragma once

#ifndef CONTAINER_CREATOR_H
#define CONTAINER_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/creators/base_creator.h>
#include <engine/actors/container.h>

#include <engine/actors/actor_factory.h>

class ContainerCreator : public BaseCreator {
private:
public:
    ContainerCreator();
    ~ContainerCreator();

    Container* createActor(json* actorData) const;
};

#endif