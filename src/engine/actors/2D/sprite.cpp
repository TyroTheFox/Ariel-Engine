#include <engine/actors/2D/sprite.h>

Sprite::Sprite(std::string id, raylib::Texture* texturePtr) {
    this->id = id;

    this->textureAtlas = new TextureAtlas(id, texturePtr);
    raylib::Vector2 textureDimentions = texturePtr->GetSize();
    this->textureAtlas->addFrame("default", raylib::Rectangle(0, 0, textureDimentions.x, textureDimentions.y));
    this->spriteFrame = "default";
}

Sprite::Sprite(std::string id, TextureAtlas* textureAtlasPtr, std::string frameID) {
    this->id = id;

    this->textureAtlas = textureAtlasPtr;
    this->spriteFrame = frameID;
}

Sprite::~Sprite() {};

void Sprite::setTexture(raylib::Texture2D* texturePtr) {
    this->textureAtlas->setAtlasTexture(texturePtr);
}

TextureAtlas* Sprite::getTextureAtlas() {
    return this->textureAtlas;
}

void Sprite::update(float dT) {}

void Sprite::render() {
    if (!this->getVisible()) {
        return;
    }

    raylib::Texture2D* atlasTexture = this->textureAtlas->getAtlasTexture();

    this->calculateRenderedPosition();

    if (atlasTexture->IsValid() && this->spriteFrame != "") {
        raylib::Rectangle frameRect = this->textureAtlas->getFrameRect(this->spriteFrame);

        raylib::Vector2 calculatedScale = raylib::Vector2(frameRect.GetWidth() * this->getScaleX(), frameRect.GetHeight() * this->getScaleY());

        raylib::Rectangle destinationRect = raylib::Rectangle(
            this->getX(), this->getY(), 
            calculatedScale.x, calculatedScale.y
        );

        atlasTexture->Draw(
            frameRect, destinationRect, 
            { calculatedScale.x * this->getAnchorX(), calculatedScale.y * this->getAnchorY() }, 
            this->getRotation(), 
            raylib::Color::White()
        );
    }
}