#pragma once

#ifndef WINDOW_BOX_CREATOR_H
#define WINDOW_BOX_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/creators/base_creator.h>
#include <engine/actors/GUI/window_box.h>

class WindowBoxCreator: public BaseCreator {
private:
public:
    WindowBoxCreator();
    ~WindowBoxCreator();

    WindowBox* createActor(json* actorData) const;
};

#endif
