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

    if (actorData->contains("scale")) {
        if (actorData->at("scale").is_number()) {
            sprite->scaleX = actorData->at("scale");
            sprite->scaleY = actorData->at("scale");
            sprite->scaleZ = actorData->at("scale");
        }

        if (actorData->at("scale").is_object()) {
            json scaleData = actorData->at("scale");

            if (scaleData.at("x")) {
                sprite->scaleX = scaleData.at("x");
            }

            if (scaleData.at("y")) {
                sprite->scaleY = scaleData.at("y");
            }

            if (scaleData.at("z")) {
                sprite->scaleZ = scaleData.at("z");
            }
        }
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            sprite->anchorX = actorData->at("anchor");
            sprite->anchorY = actorData->at("anchor");
            sprite->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                sprite->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                sprite->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                sprite->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        sprite->rotation = actorData->at("rotation");
    }

    return sprite;
}
