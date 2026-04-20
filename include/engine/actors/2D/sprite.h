#pragma once

#include <string>
#include <raylib.h>

#include <engine/actors/base_actor.h>

class Sprite : public BaseActor
{
    private:
        std::string textureID;
        Texture2D *texture;
    public:
        Sprite(std::string id, Texture2D* texturePtr);

        ~Sprite();

        void setTexture(Texture2D* texturePtr);
        void update(float dT) override;
        void render() override;
};