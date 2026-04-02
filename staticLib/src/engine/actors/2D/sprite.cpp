#pragma once

#include <string>
#include "raylib.h"

#include "engine/actors/base_actor.h"
#include "src/engine/assets/asset_loader.cpp"

class Sprite : public BaseActor
{
    private:
        std::string textureID;
        Texture2D *texture;

        TextureAssetLoader* assetLoader;
    public:
        Sprite(std::string id, TextureAssetLoader* assetLoaderPtr) {
            this->id = id;
            this->assetLoader = assetLoaderPtr;            
        }

        ~Sprite() {
            delete this->texture;
            delete this->assetLoader;
        };

        void setTexture(std::string textureID) {
            Texture2D newTexture = this->assetLoader->getTexture(textureID);

            this->textureID = textureID;

            this->texture = &newTexture;
        }

        void render() override {
            if (!this->visible) {
                return;
            }

            this->calculateRenderedPosition();

            DrawTexture(*this->texture, this->getX(), this->getY(), WHITE);
        }
};