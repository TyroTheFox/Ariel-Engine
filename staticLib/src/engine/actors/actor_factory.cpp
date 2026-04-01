#include "engine/actors/actor_factory.h"

ActorFactory::ActorFactory()
{
    this->jsonReader = new JSONReader();
    this->actorCreators = std::map<std::string, BaseCreator>{};
}

ActorFactory::~ActorFactory()
{
}