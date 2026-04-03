#pragma once

#include <string>
#include "src/engine/screen/scene.cpp";

class TestScene: public Scene
{
private:
    /* data */
public:
    TestScene() {
        this->id = "TestScene";
    }

    ~TestScene();
};