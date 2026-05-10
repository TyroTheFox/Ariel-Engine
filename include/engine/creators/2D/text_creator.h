#pragma once

#ifndef TEXT_CREATOR_H
#define TEXT_CREATOR_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/assets/sprite_font_loader.h>
#include <engine/creators/base_creator.h>
#include <engine/actors/2D/text.h>
#include <engine/utility/convert_text_to_colour.h>

class TextCreator: public BaseCreator {
private:
public:
    TextCreator();
    ~TextCreator();

    Text* createActor(json* actorData) const;
};

#endif
