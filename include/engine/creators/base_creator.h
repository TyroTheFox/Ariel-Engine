#pragma once

#ifndef BASE_CREATOR_H
#define BASE_CREATOR_H

#include <string>
#include <nlohmann/json.hpp>

#include <engine/actors/base_actor.h>

using json = nlohmann::json;

class BaseCreator {
  /**
   * Note that the Creator may also provide some default implementation of the
   * factory method.
   */
 public:  
  virtual ~BaseCreator(){};
  virtual BaseActor* createActor(json* actorData) const = 0;
};

#endif