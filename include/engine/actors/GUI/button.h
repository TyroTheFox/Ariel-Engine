#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <string.h>  
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>

class Button : public BaseActor
{
private:
    std::string text;
    float fontSize;
    int padding;

    void setDefaults();
    const char **GetTextLines(const char *text, int *count);
public:
    sl::Signal<> button_pushed;
    bool pushed = false;
    
    Button(std::string id);
    ~Button();
    
    void setText(std::string text);
    void connectActorSlot(sl::Slot<>* slot);

    void update(float dT) override;
    void render() override;
};

#endif