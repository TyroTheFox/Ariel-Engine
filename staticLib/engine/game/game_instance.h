#pragma once

#include "engine/assets/asset_loader.h"

class GameInstance
{
private:
    const AssetLoader *assetLoader;
public:
    GameInstance(/* args */);
    ~GameInstance();
};
