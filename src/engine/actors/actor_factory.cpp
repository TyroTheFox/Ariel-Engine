#include <engine/actors/actor_factory.h>

ActorFactory::ActorFactory() {
    this->jsonReader = new JSONHandler();
    this->actorCreators = std::map<std::string, void*>{};

    this->addNewCreator("container", new ContainerCreator());

    this->addNewCreator("sprite", new SpriteCreator());
    this->addNewCreator("text", new TextCreator());
    this->addNewCreator("animatedSprite", new AnimatedSpriteCreator());
    this->addNewCreator("shape", new ShapeCreator());
    
    this->addNewCreator("mesh", new MeshCreator());
    this->addNewCreator("shapeMesh", new ShapeMeshCreator());
    this->addNewCreator("billboardSprite", new BillboardSpriteCreator());

    this->addNewCreator("label", new LabelCreator());
    this->addNewCreator("button", new ButtonCreator());
    this->addNewCreator("windowBox", new WindowBoxCreator());
}

ActorFactory::~ActorFactory(){
    delete this->jsonReader;
}

void ActorFactory::addNewCreator(std::string actorType, BaseCreator* creatorPtr) {
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