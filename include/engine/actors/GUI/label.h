#pragma once

#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <string.h>  
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <raygui-4.0/src/raygui.h>

#include <engine/actors/base_actor.h>

class Label : public BaseActor
{
private:
    std::string text;
    float fontSize;
    int padding;

    void setDefaults();
    const char **GetTextLines(const char *text, int *count);
public:
    void setText(std::string text);

    Label(std::string id);
    ~Label();

    void update(float dT) override;
    void render() override;
};

#endif