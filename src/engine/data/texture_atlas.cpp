#include "engine/data/texture_atlas.h"

TextureAtlas::TextureAtlas(std::string id, raylib::Texture2D* atlasTexture) {
    this->id = id;
    this->atlasTexture = atlasTexture;
    this->frames = std::vector<AtlasFrame>{};
    this->animationMap = std::map<std::string, SpriteAnimation*>{};
}

TextureAtlas::~TextureAtlas() {
    for (auto const& [key, val] : this->animationMap)
    {
        delete val;
    }

    this->animationMap = std::map<std::string, SpriteAnimation*>{};
}

void TextureAtlas::addFrame(std::string id, raylib::Rectangle frameRect, bool rotated) {
    AtlasFrame newFrame;

    newFrame.id = id;
    newFrame.frameRect = frameRect;
    newFrame.rotated = rotated;

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

bool TextureAtlas::getFrameRotated(std::string frameID) {
    bool returnBool = false;

    for (int i = 0; i < this->frames.size(); i++) {
        if (this->frames.at(i).id == frameID) {
            returnBool = this->frames.at(i).rotated;
        }
    }

    return returnBool;
}

void TextureAtlas::setAtlasTexture(raylib::Texture2D* texturePtr) {
    this->atlasTexture = texturePtr;
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

bool TextureAtlas::atlasTextureIsValid() {
    return this->atlasTexture->IsValid();
}