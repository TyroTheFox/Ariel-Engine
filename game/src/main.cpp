#include "raylib.h"
#include "raymath.h"

#include "game.h"    // an external header in this project
#include "lib.h"    // an external header in the static lib project

#include "src/engine/game/game_instance.cpp"

int main()
{
    GameInstance gameInstance = GameInstance();

    gameInstance.startGame();

    return 0;
}