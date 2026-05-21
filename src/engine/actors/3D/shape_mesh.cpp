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

raylib::Mesh ShapeMesh::generateCube(float width, float height, float length) {
    return GenMeshCube(width, height, length);
}

raylib::Mesh ShapeMesh::generateSphere(float radius, int rings, int slices) {
    return GenMeshSphere(radius, rings, slices);
}

raylib::Mesh ShapeMesh::generateHemiSphere(float radius, int rings, int slices) {
    return GenMeshHemiSphere(radius, rings, slices);
}

raylib::Mesh ShapeMesh::generateCylinder(float radius, float height, int slices) {
    return GenMeshCylinder(radius, height, slices);
}

raylib::Mesh ShapeMesh::generatePlane(float width, float length, int resX, int resZ) {
    return GenMeshPlane(width, length, resX, resZ);
}

raylib::Mesh ShapeMesh::generateTorus(float radius, float size, int radSeg, int sides) {
    return GenMeshTorus(radius, size, radSeg, sides);
}

raylib::Mesh ShapeMesh::generateKnot(float radius, float size, int radSeg, int sides) {
    return GenMeshKnot(radius, size, radSeg, sides);
}

raylib::Mesh ShapeMesh::generatePoly(int sides, float radius) {
    return GenMeshPoly(sides, radius);
}

raylib::Mesh ShapeMesh::createMesh(json shapeData) {
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

    raylib::Mesh createdMesh;

    switch (hash(type)) {
        case "cube"_hash:
            createdMesh = this->generateCube(
                (shapeData.contains("width") ? shapeData.at("width").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("height") ? shapeData.at("height").get<float>() : 1) * this->getScaleY(),
                (shapeData.contains("length") ? shapeData.at("length").get<float>() : 1) * this->getScaleZ()
            );
        break;

        case "sphere"_hash:
            createdMesh = this->generateSphere(
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                shapeData.contains("rings") ? shapeData.at("rings").get<float>() : 1,
                shapeData.contains("slices") ? shapeData.at("slices").get<float>() : 10
            );
        break;

        case "cylinder"_hash:
            createdMesh = this->generateCylinder(
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("height") ? shapeData.at("height").get<float>() : 1) * this->getScaleY(),
                shapeData.contains("slices") ? shapeData.at("slices").get<float>() : 10
            );
        break;

        case "hemiSphere"_hash:
            createdMesh = this->generateHemiSphere(
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                shapeData.contains("rings") ? shapeData.at("rings").get<float>() : 1,
                shapeData.contains("slices") ? shapeData.at("slices").get<float>() : 10
            );
        break;

        case "torus"_hash:
            createdMesh = this->generateTorus(
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("size") ? shapeData.at("size").get<float>() : 1) * this->getScaleY(),
                shapeData.contains("radSeg") ? shapeData.at("radSeg").get<float>() : 10,
                shapeData.contains("sides") ? shapeData.at("sides").get<float>() : 10
            );
        break;

        case "knot"_hash:
            createdMesh = this->generateKnot(
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("size") ? shapeData.at("size").get<float>() : 1) * this->getScaleY(),
                shapeData.contains("radSeg") ? shapeData.at("radSeg").get<float>() : 10,
                shapeData.contains("sides") ? shapeData.at("sides").get<float>() : 10
            );
        break;

        case "plane"_hash:
            createdMesh = this->generatePlane(
                (shapeData.contains("width") ? shapeData.at("width").get<float>() : 1) * this->getScaleX(),
                (shapeData.contains("length") ? shapeData.at("length").get<float>() : 1) * this->getScaleY(),
                shapeData.contains("resX") ? shapeData.at("resX").get<float>() : 4,
                shapeData.contains("resZ") ? shapeData.at("resZ").get<float>() : 4
            );
        break;

        case "poly"_hash:
            createdMesh = this->generatePoly(
                shapeData.contains("sides") ? shapeData.at("sides").get<float>() : 5,
                (shapeData.contains("radius") ? shapeData.at("radius").get<float>() : 1) * this->getScaleX()
            );
        break;
    }

    return createdMesh;
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

void ShapeMesh::render() {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    this->processDrawData();
}