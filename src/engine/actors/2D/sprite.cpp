#include <engine/actors/2D/sprite.h>

Sprite::Sprite(std::string id, raylib::Texture* texturePtr) {
    this->id = id;
    this->texture = texturePtr;
}

Sprite::~Sprite() {};

void Sprite::setTexture(raylib::Texture2D* texturePtr) {
    this->texture = texturePtr;
}

void Sprite::update(float dT) {}

void Sprite::render() {
    if (!this->visible) {
        return;
    }

    this->calculateRenderedPosition();

    if (this->texture->IsValid()) {
        this->texture->Draw(this->getX(), this->getY(), WHITE);
    }
}