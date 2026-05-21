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

    raylib::Mesh generateCube(float width, float height, float length);
    raylib::Mesh generateSphere(float radius, int rings, int slices);
    raylib::Mesh generateHemiSphere(float radius, int rings, int slices);
    raylib::Mesh generateCylinder(float radius, float height, int slices);
    raylib::Mesh generatePlane(float width, float length, int resX, int resZ);
    raylib::Mesh generateTorus(float radius, float size, int radSeg, int sides);
    raylib::Mesh generateKnot(float radius, float size, int radSeg, int sides);
    raylib::Mesh generatePoly(int sides, float radius);

    void processDrawData();
    void renderDrawData(json shapeData);

    raylib::Mesh createMesh(json shapeData);

    void update(float dT) override;
    void render() override;
};

#endif