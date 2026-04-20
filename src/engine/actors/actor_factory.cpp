#include <engine/actors/actor_factory.h>

ActorFactory::ActorFactory(TextureAssetLoader* textureAssetLoaderPtr) {
    SpriteCreator* spriteCreator = new SpriteCreator();
    spriteCreator->textureAssetLoader = textureAssetLoaderPtr;

    this->jsonReader = new JSONHandler();
    this->actorCreators = std::map<std::string, void*>{};

    this->actorCreators.insert({ "sprite", spriteCreator });
}

ActorFactory::~ActorFactory(){
    delete this->jsonReader;
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