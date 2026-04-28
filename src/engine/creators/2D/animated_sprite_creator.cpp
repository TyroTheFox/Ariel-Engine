#include "engine/creators/2D/animated_sprite_creator.h"

AnimatedSpriteCreator::AnimatedSpriteCreator() {}
AnimatedSpriteCreator::~AnimatedSpriteCreator() {}

AnimatedSprite* AnimatedSpriteCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");
    std::string textureID = actorData->at("texture");

    raylib::Texture2D* texture = this->textureAssetLoader->getTexturePtr(textureID);

    AnimatedSprite* animatedSprite = new AnimatedSprite(id, texture);

    if (actorData->contains("x")) {
        animatedSprite->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        animatedSprite->y = actorData->at("y");
    }

    if (actorData->contains("visible")) {
        animatedSprite->visible = actorData->at("visible");
    }

    if (actorData->contains("builtAnimations")) {
        json animationsList = actorData->at("builtAnimations");

        for (auto& animationEntry : animationsList) {
            if (animationEntry.contains("frames")) {
                auto frames = animationEntry.at("frames");
                for (auto& frameEntry : frames) {
                    std::tuple<raylib::Rectangle, std::string> frameTuple = this->textureAssetLoader->getFrameData(frameEntry);

                    raylib::Rectangle frameRect = std::get<0>(frameTuple);

                    animatedSprite->addFrame(frameEntry, frameRect);
                }

                animatedSprite->addAnimation(animationEntry.at("id"), animationEntry.at("frames"));
            }
        }
    }

    if (actorData->contains("frameSpeed")) {
        animatedSprite->setFrameSpeed(actorData->at("frameSpeed"));
    }

    if (actorData->contains("loop")) {
        animatedSprite->setLoopCount(actorData->at("loop"));
    }

    return animatedSprite;
}