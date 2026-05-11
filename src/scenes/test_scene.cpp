#include "scenes/test_scene.h"

TestScene::TestScene(std::string id, json sceneData) : Scene(id, sceneData) {
    AnimatedSprite* testAnimatedSprite = dynamic_cast<AnimatedSprite*>(this->getActorByID("test_animated_sprite"));
    BillboardSprite* testBillboard = dynamic_cast<BillboardSprite*>(this->getActorByID("test_billboard"));

    testBillboard->setSceneCamera(this->camera3D);

    this->testCube = dynamic_cast<MeshModel*>(this->getActorByID("test_model"));

    testAnimatedSprite->playAnimation("clubs");
    testBillboard->playAnimation("hearts");

    this->camera3D->SetTarget({testCube->getX(), testCube->getY(), testCube->getY()});

    this->signal_update.connect(this->updateSlot);
}

void TestScene::onUpdate(float dT) const {
    if (this->testCube->getRotation() >= 360.0f) {
        this->testCube->rotation = 0.0f;
    }

    this->testCube->rotation += 5.0f;
}