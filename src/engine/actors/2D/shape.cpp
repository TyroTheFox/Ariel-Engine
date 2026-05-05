#include "engine/actors/2D/shape.h"

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

Shape::Shape(std::string id) {
    this->actorRenderType = ACTOR_2D;
    
    this->id = id;
}

Shape::~Shape() {
}

void Shape::drawCircle(int centerX, int centerY, int radius, raylib::Color color) {
    ::DrawCircle(
        centerX + static_cast<int>(this->getX()), 
        centerY + static_cast<int>(this->getY()), 
        radius, color
    );
}

void Shape::drawLine(int startPosX, int startPosY,	int endPosX, int endPosY, raylib::Color color) {
    ::DrawLine(        
        startPosX + static_cast<int>(this->getX()), 
        startPosY + static_cast<int>(this->getY()), 
        endPosX + static_cast<int>(this->getX()), 
        endPosY + static_cast<int>(this->getY()), 
        color
    );
}
void Shape::drawPixel(int posX, int posY, raylib::Color color) {
    ::DrawPixel(
        posX + static_cast<int>(this->getX()), 
        posY + static_cast<int>(this->getY()), 
        color
    );
}

void Shape::drawRectangle(int posX, int posY, int width, int height, raylib::Color color) {
    ::DrawRectangle(
        posX + static_cast<int>(this->getX()), 
        posY + static_cast<int>(this->getY()), 
        width * static_cast<int>(this->getScaleX()), 
        height * static_cast<int>(this->getScaleY()), 
        color
    );
}

void Shape::drawRoundedRectangle(raylib::Rectangle rec, int roundness, int segments, raylib::Color color) {
    rec.x += static_cast<int>(this->getX());
    rec.y += static_cast<int>(this->getY());
    rec.width *= static_cast<int>(this->getScaleX());
    rec.height *= static_cast<int>(this->getScaleY());
    
    ::DrawRectangleRounded(rec, roundness, segments, color);
}

void Shape::processDrawData() {    
    if (this->drawData.is_array()) {
        for (auto& entry : this->drawData) {
            this->renderDrawData(entry);
        }
    }

    if (this->drawData.is_object()) {
        this->renderDrawData(this->drawData);
    }
}

void Shape::renderDrawData(json shapeData) {
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
        case "circle"_hash:
            drawCircle(shapeData.at("x"), shapeData.at("y"), shapeData.at("radius"), shapeColour);
        break;

        case "line"_hash:
            drawLine(shapeData.at("startX"), shapeData.at("startY"), shapeData.at("endX"), shapeData.at("endY"), shapeColour);
        break;

        case "pixel"_hash:
            drawPixel(shapeData.at("x"), shapeData.at("y"), shapeColour);
        break;

        case "rectangle"_hash:
            drawRectangle(shapeData.at("x"), shapeData.at("y"), shapeData.at("width"), shapeData.at("height"), shapeColour);
        break;

        case "roundedRectangle"_hash:
            drawRoundedRectangle(
                raylib::Rectangle(
                    shapeData.at("x"),
                    shapeData.at("y"),
                    shapeData.at("width"),
                    shapeData.at("height")
                ),
                shapeData.at("roundness"),
                shapeData.at("segments"),
                shapeColour
            );
        break;
    }
}

void Shape::update(float dT) {}

void Shape::render() {
    if (!this->getVisible()) {
        return;
    }

    this->calculateRenderedPosition();

    this->processDrawData();
}