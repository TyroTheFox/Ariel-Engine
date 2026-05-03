#pragma once

#ifndef BASE_CREATOR_H
#define BASE_CREATOR_H

#include <string>

#include <engine/actors/base_actor.h>
#include <engine/assets/asset_loader.h>

class BaseCreator {
  /**
   * Note that the Creator may also provide some default implementation of the
   * factory method.
   */
 public:
  AssetLoader* assetLoader;
  
  virtual ~BaseCreator(){};
  virtual BaseActor* createActor(json* actorData) const = 0;
};

#endif