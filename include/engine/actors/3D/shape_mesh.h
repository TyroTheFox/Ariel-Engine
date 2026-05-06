#pragma once

#ifndef SHAPE_MESH_H
#define SHAPE_MESH_H

#include <string>
#include <nlohmann/json.hpp>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>

#include <cstdint>
#include <string_view>
#include <iostream>

#include <engine/utility/convert_text_to_colour.h>

constexpr uint64_t hash(std::string_view str);

constexpr uint64_t operator"" _hash(const char* str, size_t len);

using json = nlohmann::json;

class ShapeMesh : public BaseActor {
private:
public:
    json drawData;

    ShapeMesh(std::string id);
    ~ShapeMesh();

    void drawCube(Vector3 position, float width, float height, float length, raylib::Color color);
    void drawCubeWires(Vector3 position, float width, float height, float length, raylib::Color color);

    void drawSphere(Vector3 centerPos, float radius, raylib::Color color);
    void drawSphereWires(Vector3 centerPos, float radius, raylib::Color color);

    void drawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int sides, raylib::Color color);
    void drawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int sides, raylib::Color color);

    void drawCapsule(Vector3 startPos, Vector3 endPos, float radius, float rings, int slices, Color color);
    void drawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, float rings, int slices, Color color);

    void drawPlane(Vector3 centerPos, Vector2 size, Color color);

    void drawRay(raylib::Ray ray, raylib::Color color);
    
    void drawGrid(int slices, float spacing);

    void processDrawData();
    void renderDrawData(json shapeData);

    void update(float dT) override;
    void render() override;
};

#endif