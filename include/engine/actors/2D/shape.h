#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <nlohmann/json.hpp>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>
#include <engine/render/rendering_shader.h>

#include <cstdint>
#include <string_view>
#include <iostream>

#include <engine/utility/convert_text_to_colour.h>

constexpr uint64_t hash(std::string_view str);

constexpr uint64_t operator"" _hash(const char* str, size_t len);

using json = nlohmann::json;

class Shape : public BaseActor {
private:
public:
    json drawData;

    Shape(std::string id);
    ~Shape();

    void drawCircle(int centerX, int centerY, int radius, raylib::Color color = {255, 255, 255, 255});
    void drawLine(int startPosX, int startPosY,	int endPosX, int endPosY, raylib::Color color = {255, 255, 255, 255});
    void drawPixel(int posX, int posY, raylib::Color color = {255, 255, 255, 255});
    void drawRectangle(int posX, int posY, int width, int height, raylib::Color color = {255, 255, 255, 255});
    void drawRoundedRectangle(raylib::Rectangle rec, int roundness, int segments, raylib::Color color = {255, 255, 255, 255});

    void processDrawData();
    void renderDrawData(json shapeData);

    void update(float dT) override;
    void render(RenderingShader* shader) override;
};

#endif