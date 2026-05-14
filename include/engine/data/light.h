#pragma once

#ifndef LIGHT_H
#define LIGHT_H

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

typedef enum {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT,
    LIGHT_SPOT
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
    float intensity;

    // Shader locations
    int enabledLoc;
    int typeLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int attenuationLoc;
    int intensityLoc;
public:
    Light(std::string id, int type, int lightsCount, raylib::Vector3 position, raylib::Vector3 target, float intensity, raylib::Color color, raylib::Shader* shader);
    ~Light();

    raylib::Color getColor();
    bool isEnabled();
    raylib::Vector3 getPosition();
    void UpdateLightValues(raylib::Shader* shader);
};

#endif