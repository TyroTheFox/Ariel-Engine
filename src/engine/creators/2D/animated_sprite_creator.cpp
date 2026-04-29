#include "engine/creators/2D/animated_sprite_creator.h"

AnimatedSpriteCreator::AnimatedSpriteCreator() {}
AnimatedSpriteCreator::~AnimatedSpriteCreator() {}

AnimatedSprite* AnimatedSpriteCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");
    std::string textureID = actorData->at("texture");
    std::string firstFrameName = this->textureAssetLoader->getTextureAtlas(textureID)->getFrameList().at(0).id;
    std::string defaultFrame = actorData->contains("defaultFrame") ? actorData->at("defaultFrame").get<std::string>() : firstFrameName;

    TextureAtlas* textureAtlas = this->textureAssetLoader->getTextureAtlas(textureID);

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
    
    if (actorData->contains("frameSpeed")) {
        animatedSprite->setFrameSpeed(actorData->at("frameSpeed"));
    }

    if (actorData->contains("loop")) {
        animatedSprite->setLoopCount(actorData->at("loop"));
    }

    return animatedSprite;
}