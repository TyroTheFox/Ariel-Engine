#pragma once

#include <map>
#include "raylib.h"

#include "engine/utility/json_reader.h"
#include "engine/actors/base_creator.h"

class ActorFactory
{
private:
    JSONReader *jsonReader;
    std::map<std::string, BaseCreator> actorCreators;
public:
    ActorFactory();
    ~ActorFactory();
};
