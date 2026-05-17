#pragma once

#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>

class Text : public BaseActor
{
private:
    raylib::Text raylibText;

    float fontSize;
    float spacing;
    
    bool wordWrap;
    raylib::Rectangle bounds;
    void setDefaults(raylib::Font* fontPtr);
public:
    Text(std::string id);
    Text(std::string id, raylib::Font* fontPtr);
    ~Text();

    void setFont(raylib::Font* fontPtr);
    void setText(std::string text);
    void setColour(raylib::Color colour);
    void setSpacing(float spacing);

    void setWordWrap(bool wordWrap);
    void setWordWrapBounds(raylib::Rectangle rect);

    void drawTextWithWordWrap();

    void update(float dT) override;
    void render() override;
};

#endif