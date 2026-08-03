#pragma once

#ifndef WINDOW_BOX_H
#define WINDOW_BOX_H

#include <string>
#include <string.h>  
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>

class WindowBox : public BaseActor
{
private:
    void setDefaults();
public:
    WindowBox(std::string id);
    ~WindowBox();
    
    void update(float dT) override;
    void render() override;
};

#endif