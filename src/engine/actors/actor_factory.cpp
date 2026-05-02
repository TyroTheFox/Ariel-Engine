#include <engine/actors/actor_factory.h>

ActorFactory::ActorFactory(TextureAssetLoader* textureAssetLoaderPtr, SpriteFontLoader* spriteFontLoaderPtr) {
    this->textureAssetLoader = textureAssetLoaderPtr;
    this->spriteFontLoader = spriteFontLoaderPtr;

    this->jsonReader = new JSONHandler();
    this->actorCreators = std::map<std::string, void*>{};

    this->addNewCreator("sprite", new SpriteCreator());
    this->addNewCreator("text", new TextCreator());
    this->addNewCreator("animatedSprite", new AnimatedSpriteCreator());
    this->addNewCreator("shape", new ShapeCreator());
}

ActorFactory::~ActorFactory(){
    delete this->jsonReader;
}

void ActorFactory::addNewCreator(std::string actorType, BaseCreator* creatorPtr) {
    creatorPtr->textureAssetLoader = this->textureAssetLoader;
    creatorPtr->spriteFontLoader = this->spriteFontLoader;

    this->actorCreators.insert({ actorType, creatorPtr });
}

BaseActor* ActorFactory::createActor(json* actorData) {
    std::string actorType = actorData->at("type");

    auto it = this->actorCreators.find(actorType);

    if (it == this->actorCreators.end()) {
        // Element Not Found
        return nullptr;
    }

    auto creator = static_cast<BaseCreator*>(this->actorCreators.at(actorType));

    auto newActor = creator->createActor(actorData);

    return newActor;
}