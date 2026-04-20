#include <engine/actors/2D/sprite.h>

Sprite::Sprite(std::string id, Texture2D* texturePtr) {
    this->id = id;
    this->texture = texturePtr;
    this->textureID = this->texture->id;
}

Sprite::~Sprite() {
    delete this->texture;
};

void Sprite::setTexture(Texture2D* texturePtr) {
    this->texture = texturePtr;
    this->textureID = this->texture->id;
}

void Sprite::update(float dT) {}

void Sprite::render() {
    if (!this->visible) {
        return;
    }

    this->calculateRenderedPosition();

    DrawTexture(*this->texture, this->getX(), this->getY(), WHITE);
}