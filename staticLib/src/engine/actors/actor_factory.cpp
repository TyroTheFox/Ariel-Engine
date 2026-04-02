#pragma once

#include <map>
#include "raylib.h"

#include "engine/utility/json_reader.h"
#include "engine/creators/base_creator.h"

class ActorFactory
{
private:
    JSONReader *jsonReader;
    std::map<std::string, BaseCreator> actorCreators;
public:
    ActorFactory();
    ~ActorFactory();
};

ActorFactory::ActorFactory()
{
    this->jsonReader = new JSONReader();
    this->actorCreators = std::map<std::string, BaseCreator>{};
}

ActorFactory::~ActorFactory()
{
}