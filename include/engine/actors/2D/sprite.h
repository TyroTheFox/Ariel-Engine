#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/actors/base_actor.h>
#include <engine/data/texture_atlas.h>

class Sprite : public BaseActor
{
    private:
        TextureAtlas* textureAtlas;
        std::string spriteFrame;
    public:
        Sprite(std::string id, raylib::Texture* texturePtr);
        Sprite(std::string id, TextureAtlas* textureAtlasPtr, std::string frameID);
        ~Sprite();

        void setTexture(raylib::Texture2D* texturePtr);
        TextureAtlas* getTextureAtlas();
        void update(float dT) override;
        void render() override;
};

#endif