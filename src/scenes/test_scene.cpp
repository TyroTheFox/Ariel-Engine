#include "scenes/test_scene.h"

TestScene::TestScene() : Scene() {
}

TestScene::TestScene(std::string id, json sceneData, ActorFactory* actorFactoryPtr) : Scene(id, sceneData, actorFactoryPtr) {
    AnimatedSprite* testAnimatedSprite = dynamic_cast<AnimatedSprite*>(this->getActorByID("test_animated_sprite"));

    testAnimatedSprite->playAnimation("clubs");
}