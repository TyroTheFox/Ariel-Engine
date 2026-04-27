#pragma once

#ifndef STRING_H
#define STRING_H

#include <string>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>

class Sprite : public BaseActor
{
    private:
        raylib::Texture2D* texture;
    public:
        Sprite(std::string id, raylib::Texture* texturePtr);

        ~Sprite();

        void setTexture(raylib::Texture2D* texturePtr);
        void update(float dT) override;
        void render() override;
};

#endif