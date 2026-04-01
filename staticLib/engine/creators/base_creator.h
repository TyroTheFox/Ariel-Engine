#pragma once

#include <string>

#include "engine/actors/base_actor.h"

class BaseCreator {
  /**
   * Note that the Creator may also provide some default implementation of the
   * factory method.
   */
 public:
  virtual ~BaseCreator(){};
  virtual BaseActor* FactoryMethod() const = 0;
};