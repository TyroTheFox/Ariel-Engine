#include "engine/actors/3D/shape_mesh.h"

constexpr uint64_t hash(std::string_view str) {
    uint64_t hash = 0;
    for (char c : str) {
        hash = (hash * 131) + c;
    }
    return hash;
}

constexpr uint64_t operator"" _hash(const char* str, size_t len) {
    return hash(std::string_view(str, len));
}

ShapeMesh::ShapeMesh(std::string id) {
    this->id = id;
    this->actorType = "ShapeMesh";
    this->actorRenderType = ACTOR_3D;
}

ShapeMesh::~ShapeMesh() {
}

void ShapeMesh::drawCube(Vector3 position, float width, float height, float length, raylib::Color color) {
    ::DrawCube(position, width, height, length, color);
}

void ShapeMesh::drawCubeWires(Vector3 position, float width, float height, float length, raylib::Color color) {
    ::DrawCubeWires(position, width, height, length, color);
}

void ShapeMesh::drawSphere(Vector3 centerPos, float radius, raylib::Color color) {
    ::DrawSphere(centerPos, radius, color);
}

void ShapeMesh::drawSphereWires(Vector3 centerPos, float radius, raylib::Color color) {
    ::DrawSphere(centerPos, radius, color);
}

void ShapeMesh::drawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int sides, raylib::Color color) {
    ::DrawCylinder(position, radiusTop, radiusBottom, height, sides, color);
}

void ShapeMesh::drawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int sides, raylib::Color color) {
    ::DrawCylinderWires(position, radiusTop, radiusBottom, height, sides, color);
}

void ShapeMesh::drawCapsule(Vector3 startPos, Vector3 endPos, float radius, float rings, int slices, Color color) {
    ::DrawCapsule(startPos, endPos, radius, rings, slices, color);
}

void ShapeMesh::drawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, float rings, int slices, Color color) {
    ::DrawCapsuleWires(startPos, endPos, radius, rings, slices, color);
}

void ShapeMesh::drawPlane(Vector3 centerPos, Vector2 size, Color color) {
    ::DrawPlane(centerPos, size, color);
}

void ShapeMesh::drawRay(raylib::Ray ray, raylib::Color color) {
    ::DrawRay(ray, color);
}

void ShapeMesh::drawGrid(int slices, float spacing) {
    ::DrawGrid(slices, spacing);
}

void ShapeMesh::processDrawData() {    
    if (this->drawData.is_array()) {
        for (auto& entry : this->drawData) {
            this->renderDrawData(entry);
        }
    }

    if (this->drawData.is_object()) {
        this->renderDrawData(this->drawData);
    }
}

void ShapeMesh::renderDrawData(json shapeData) {
    std::string type = shapeData.at("shape");
    raylib::Color shapeColour = raylib::Color::White();

    if (shapeData.contains("color")) {
        json colorData = shapeData.at("color");

        if (colorData.is_string()) {
            shapeColour = convertTextToColour(colorData.get<std::string>());
        }

        if (colorData.is_object()) {
            shapeColour.r = colorData.contains("r") ? colorData.at("r").get<char>() : 255;
            shapeColour.g = colorData.contains("g") ? colorData.at("g").get<char>() : 255;
            shapeColour.b = colorData.contains("b") ? colorData.at("b").get<char>() : 255;
            shapeColour.a = colorData.contains("a") ? colorData.at("a").get<char>() : 255;
        }
    }

    switch (hash(type)) {
        case "cube"_hash:
            this->drawCube(
                {
                    .x = this->getX(),
                    .y = this->getY(),
                    .z = this->getZ()
                }, 
                (shapeData.contains("width") ? shapeData.at("width").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("height") ? shapeData.at("height").get<float>() : 1) * this->getScaleY(),
                (shapeData.contains("length") ? shapeData.at("length").get<float>() : 1) * this->getScaleZ(),
                shapeColour
            );
        break;

        case "cubeWires"_hash:
            this->drawCubeWires(
                {
                    .x = this->getX(),
                    .y = this->getY(),
                    .z = this->getZ()
                }, 
                (shapeData.contains("width") ? shapeData.at("width").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("height") ? shapeData.at("height").get<float>() : 1) * this->getScaleY(),
                (shapeData.contains("length") ? shapeData.at("length").get<float>() : 1) * this->getScaleZ(),
                shapeColour
            );
        break;

        case "sphere"_hash:
            this->drawSphere(
                {
                    .x = this->getX(),
                    .y = this->getY(),
                    .z = this->getZ()
                },
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                shapeColour
            );
        break;

        case "sphereWires"_hash:
            this->drawSphereWires(
                {
                    .x = this->getX(),
                    .y = this->getY(),
                    .z = this->getZ()
                },
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                shapeColour
            );
        break;

        case "cylinder"_hash:
            this->drawCylinder(
                {
                    .x = this->getX(),
                    .y = this->getY(),
                    .z = this->getZ()
                },
                (shapeData.contains("radiusTop") ? shapeData.at("radiusTop").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("radiusBottom") ? shapeData.at("radiusBottom").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("height") ? shapeData.at("height").get<float>() : 1) * this->getScaleY(),
                (shapeData.contains("sides") ? shapeData.at("sides").get<int>() : 1),
                shapeColour
            );
        break;

        case "cylinderWires"_hash:
            this->drawCylinderWires(
                {
                    .x = this->getX(),
                    .y = this->getY(),
                    .z = this->getZ()
                },
                (shapeData.contains("radiusTop") ? shapeData.at("radiusTop").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("radiusBottom") ? shapeData.at("radiusBottom").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("height") ? shapeData.at("height").get<float>() : 1) * this->getScaleY(),
                (shapeData.contains("sides") ? shapeData.at("sides").get<int>() : 1),
                shapeColour
            );
        break;

        case "capsule"_hash:
            this->drawCapsule(
                {
                    .x = this->getX() + (shapeData.contains("startX") ? shapeData.at("startX").get<float>() : 0),
                    .y = this->getY() + (shapeData.contains("startY") ? shapeData.at("startY").get<float>() : 0),
                    .z = this->getZ() + (shapeData.contains("startZ") ? shapeData.at("startZ").get<float>() : 0)
                },
                {
                    .x = this->getX() + (shapeData.contains("endX") ? shapeData.at("endX").get<float>() : 0),
                    .y = this->getY() + (shapeData.contains("endY") ? shapeData.at("endY").get<float>() : 0),
                    .z = this->getZ() + (shapeData.contains("endZ") ? shapeData.at("endZ").get<float>() : 0)
                },
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("rings") ? shapeData.at("rings").get<float>() : 1),
                (shapeData.contains("slices") ? shapeData.at("slices").get<float>() : 1),
                shapeColour
            );
        break;

        case "capsuleWires"_hash:
            this->drawCapsule(
                {
                    .x = this->getX() + (shapeData.contains("startX") ? shapeData.at("startX").get<float>() : 0),
                    .y = this->getY() + (shapeData.contains("startY") ? shapeData.at("startY").get<float>() : 0),
                    .z = this->getZ() + (shapeData.contains("startZ") ? shapeData.at("startZ").get<float>() : 0)
                },
                {
                    .x = this->getX() + (shapeData.contains("endX") ? shapeData.at("endX").get<float>() : 0),
                    .y = this->getY() + (shapeData.contains("endY") ? shapeData.at("endY").get<float>() : 0),
                    .z = this->getZ() + (shapeData.contains("endZ") ? shapeData.at("endZ").get<float>() : 0)
                },
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("rings") ? shapeData.at("rings").get<float>() : 1),
                (shapeData.contains("slices") ? shapeData.at("slices").get<float>() : 1),
                shapeColour
            );
        break;
    }
}

void ShapeMesh::update(float dT) {}

void ShapeMesh::render(RenderingShader* shader) {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    this->processDrawData();
}