#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

typedef enum {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT
} LightType;

class Light
{
private:
    std::string id;
    int lightID;

    int type;
    bool enabled;
    raylib::Vector3 position;
    raylib::Vector3 target;
    raylib::Color color;
    float attenuation;

    // Shader locations
    int enabledLoc;
    int typeLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int attenuationLoc;
public:
    Light(std::string id, int type, int lightsCount, raylib::Vector3 position, raylib::Vector3 target, raylib::Color color, raylib::Shader* shader);
    ~Light();

    void UpdateLightValues(raylib::Shader* shader);
};

#endif