#pragma once

#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

#include <map>
#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/globals.h>

class GameInstance {
    private:
        const int screenWidth = 1600;
        const int screenHeight = 900;
        const int targetFPS = 60;
    public:
        raylib::Window* gameWindow;
        
        GameInstance();
        ~GameInstance();

        void instantiateGame(std::string assetManifestPath);
        void startGame();
};

#endif