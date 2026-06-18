#pragma once

#ifndef LABEL_CREATOR_H
#define LABEL_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/creators/base_creator.h>
#include <engine/actors/GUI/label.h>

class LabelCreator: public BaseCreator {
private:
public:
    LabelCreator();
    ~LabelCreator();

    Label* createActor(json* actorData) const;
};

#endif
