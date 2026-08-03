#pragma once

#ifndef BUTTON_CREATOR_H
#define BUTTON_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/creators/base_creator.h>
#include <engine/actors/GUI/button.h>

class ButtonCreator: public BaseCreator {
private:
public:
    ButtonCreator();
    ~ButtonCreator();

    Button* createActor(json* actorData) const;
};

#endif
