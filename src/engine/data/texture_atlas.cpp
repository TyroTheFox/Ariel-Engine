#include "engine/data/texture_atlas.h"

TextureAtlas::TextureAtlas(std::string id, raylib::Texture2D* atlasTexture) {
    this->id = id;
    this->atlasTexture = atlasTexture;
    this->frames = std::vector<AtlasFrame>{};
    this->animationMap = std::map<std::string, SpriteAnimation*>{};
}

TextureAtlas::~TextureAtlas() {
}

void TextureAtlas::addFrame(std::string id, raylib::Rectangle frameRect) {
    AtlasFrame newFrame;

    newFrame.id = id;
    newFrame.frameRect = frameRect;

    this->frames.push_back(newFrame);
}

raylib::Rectangle TextureAtlas::getFrameRect(std::string frameID) {
    raylib::Rectangle returnRect(0, 0, 0, 0);

    for (int i = 0; i < this->frames.size(); i++) {
        if (this->frames.at(i).id == frameID) {
            returnRect = this->frames.at(i).frameRect;
        }
    }

    return returnRect;
}

raylib::Texture2D* TextureAtlas::getAtlasTexture() {
    return this->atlasTexture;
}

std::vector<AtlasFrame> TextureAtlas::getFrameList() {
    return this->frames;
}

void TextureAtlas::addAnimation(std::string key, std::vector<std::string> frameList, int playSpeed, int loopCount) {
    struct SpriteAnimation* newAnimation = new SpriteAnimation;

    newAnimation->id = key;
    newAnimation->frames = frameList;
    newAnimation->playSpeed = playSpeed;
    newAnimation->loopCount = loopCount;

    this->animationMap.insert({key, newAnimation});
}

SpriteAnimation* TextureAtlas::getAnimation(std::string animationId) {
    auto it = this->animationMap.find(animationId);

    if (it == this->animationMap.end()) {
        // Element Not Found
        return nullptr;
    }

    SpriteAnimation* spriteAnimation = this->animationMap.at(animationId);

    return spriteAnimation;
}