#pragma once

#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include <string>
#include <engine/screen/scene.h>

class TestScene: public Scene
{
private:
    sl::Slot<float> updateSlot{this, &TestScene::onUpdate};

    MeshModel* testCube;
public:
    TestScene(std::string id, json sceneData);
    ~TestScene();

    void onUpdate(float dT) const;
};

#endif