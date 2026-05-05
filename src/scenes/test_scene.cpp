#include "scenes/test_scene.h"

TestScene::TestScene() : Scene() {
}

TestScene::TestScene(std::string id, json sceneData, ActorFactory* actorFactoryPtr) : Scene(id, sceneData, actorFactoryPtr) {
    AnimatedSprite* testAnimatedSprite = dynamic_cast<AnimatedSprite*>(this->getActorByID("test_animated_sprite"));
    this->testCube = dynamic_cast<MeshModel*>(this->getActorByID("test_model"));

    testAnimatedSprite->playAnimation("clubs");

    this->camera3D->SetTarget({testCube->getX(), testCube->getY(), testCube->getY()});

    this->signal_update.connect(this->updateSlot);
}

void TestScene::onUpdate(float dT) const {
    if (this->testCube->getRotation() >= 360.0f) {
        this->testCube->rotation = 0.0f;
    }

    this->testCube->rotation += 5.0f;
}