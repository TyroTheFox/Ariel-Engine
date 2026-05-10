#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include "engine/assets/asset_loader.h"
#include "engine/actors/actor_factory.h"
#include "engine/screen/stage_manager.h"
#include "engine/game/game_instance.h"

namespace Ariel {
    namespace Global {
        extern AssetLoader assetLoader;

        extern ActorFactory actorFactory;

        extern StageManager stageManager;

        extern GameInstance gameInstance;
    }
}

#endif