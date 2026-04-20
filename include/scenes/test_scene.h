#pragma once

#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <string>
#include <engine/screen/scene.h>

class TestScene: public Scene
{
private:
    /* data */
public:
    TestScene();
    TestScene(std::string id, json sceneData, ActorFactory* actorFactoryPtr);
    ~TestScene();
};

#endif