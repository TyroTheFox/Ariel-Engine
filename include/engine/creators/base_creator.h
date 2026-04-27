#pragma once

#ifndef BASE_CREATOR_H
#define BASE_CREATOR_H

#include <string>

#include <engine/actors/base_actor.h>
#include <engine/assets/texture_asset_loader.h>
#include <engine/assets/sprite_font_loader.h>

class BaseCreator {
  /**
   * Note that the Creator may also provide some default implementation of the
   * factory method.
   */
 public:
  TextureAssetLoader* textureAssetLoader;
  SpriteFontLoader* spriteFontLoader;
  
  virtual ~BaseCreator(){};
  virtual BaseActor* createActor(json* actorData) const = 0;
};

#endif