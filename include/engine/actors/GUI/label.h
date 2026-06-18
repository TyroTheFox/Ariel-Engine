#pragma once

#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <engine/actors/base_actor.h>

class Label : public BaseActor
{
private:
    std::string text;
    float fontSize;

    void setDefaults(raylib::Font* fontPtr);
public:
    void setText(std::string text);

    Label(std::string id);
    ~Label();

    void update(float dT) override;
    void render() override;
};

#endif