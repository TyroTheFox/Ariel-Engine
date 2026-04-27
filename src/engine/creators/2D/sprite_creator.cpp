#include <engine/creators/2D/sprite_creator.h>

SpriteCreator::SpriteCreator() {}
SpriteCreator::~SpriteCreator() {}

Sprite* SpriteCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");
    std::string textureID = actorData->at("texture");

    raylib::Texture2D* texture = this->textureAssetLoader->getTexturePtr(textureID);

    Sprite* sprite = new Sprite(id, texture);

    if (actorData->contains("x")) {
        sprite->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        sprite->y = actorData->at("y");
    }

    if (actorData->contains("visible")) {
        sprite->visible = actorData->at("visible");
    }

    return sprite;
}
