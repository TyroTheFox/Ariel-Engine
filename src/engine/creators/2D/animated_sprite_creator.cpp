#include "engine/creators/2D/animated_sprite_creator.h"

AnimatedSpriteCreator::AnimatedSpriteCreator() {}
AnimatedSpriteCreator::~AnimatedSpriteCreator() {}

AnimatedSprite* AnimatedSpriteCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");
    std::string textureID = actorData->at("texture");
    std::string firstFrameName = Ariel::Global::assetLoader.getTextureAtlas(textureID)->getFrameList().at(0).id;
    std::string defaultFrame = actorData->contains("defaultFrame") ? actorData->at("defaultFrame").get<std::string>() : firstFrameName;

    TextureAtlas* textureAtlas = Ariel::Global::assetLoader.getTextureAtlas(textureID);

    AnimatedSprite* animatedSprite = new AnimatedSprite(id, textureAtlas, defaultFrame);

    if (actorData->contains("x")) {
        animatedSprite->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        animatedSprite->y = actorData->at("y");
    }

    if (actorData->contains("visible")) {
        animatedSprite->visible = actorData->at("visible");
    }

    if (actorData->contains("scale")) {
        if (actorData->at("scale").is_number()) {
            animatedSprite->scaleX = actorData->at("scale");
            animatedSprite->scaleY = actorData->at("scale");
            animatedSprite->scaleZ = actorData->at("scale");
        }

        if (actorData->at("scale").is_object()) {
            json scaleData = actorData->at("scale");

            if (scaleData.at("x")) {
                animatedSprite->scaleX = scaleData.at("x");
            }

            if (scaleData.at("y")) {
                animatedSprite->scaleY = scaleData.at("y");
            }

            if (scaleData.at("z")) {
                animatedSprite->scaleZ = scaleData.at("z");
            }
        }
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            animatedSprite->anchorX = actorData->at("anchor");
            animatedSprite->anchorY = actorData->at("anchor");
            animatedSprite->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                animatedSprite->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                animatedSprite->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                animatedSprite->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        animatedSprite->rotation = actorData->at("rotation");
    }

    return animatedSprite;
}