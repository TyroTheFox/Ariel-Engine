#include <engine/creators/2D/sprite_creator.h>

SpriteCreator::SpriteCreator() {}
SpriteCreator::~SpriteCreator() {}

Sprite* SpriteCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");
    std::string textureID = actorData->at("texture");

    Texture2D* texture = this->textureAssetLoader->getTexturePtr(textureID);

    Sprite* sprite = new Sprite(id, texture);

    return sprite;
}
