#include <engine/screen/scene.h>

Scene::Scene() {
    this->id = "scene";
    this->baseContainer = new Container("scene_Container");
    this->children = std::map<std::string, BaseActor*>{};

    this->camera2D = new raylib::Camera2D();
    this->camera3D = new raylib::Camera3D();
}

Scene::Scene(std::string name, json sceneData, ActorFactory* actorFactoryPtr) {
    this->id = name;
    this->baseContainer = new Container(name + "_Container");
    this->children = std::map<std::string, BaseActor*>{};

    this->actorFactory = actorFactoryPtr;

    this->settingsData = &sceneData.at("settings");
    this->actorData = &sceneData.at("actors");

    for (json entry : sceneData.at("actors")) {
        std::string actorId = entry.at("id");

        BaseActor* newActor = this->actorFactory->createActor(&entry);
        newActor->id = actorId;

        this->addActor(newActor);
    }

    Camera2DSettings camera2DSettings {
        .offset = {0.0f, 0.0f},
        .position = {0.0f, 0.0f},
        .rotation = 0.0f,
        .zoom = 1.0f
    };

    Camera3DSettings camera3DSettings {
        .position = {0.0f, 0.0f, 0.0f},
        .target = {0.0f, 0.0f, 0.0f},
        .up = {0.0f, 1.0f, 0.0f},
        .fov = 45.0f
    };

    if (this->settingsData->contains("camera2D")) {
        json camera2DData = this->settingsData->at("camera2D");
        if (camera2DData.contains("x")) {
            camera2DSettings.position.x = camera2DData.at("x");
        }

        if (camera2DData.contains("y")) {
            camera2DSettings.position.y = camera2DData.at("y");
        }

        if (camera2DData.contains("offsetX")) {
            camera2DSettings.offset.x = camera2DData.at("offsetX");
        }

        if (camera2DData.contains("offsetY")) {
            camera2DSettings.offset.y = camera2DData.at("offsetY");
        }

        if (camera2DData.contains("rotation")) {
            camera2DSettings.rotation = camera2DData.at("rotation");
        }

        if (camera2DData.contains("zoom")) {
            camera2DSettings.zoom = camera2DData.at("zoom");
        }
    }

    if (this->settingsData->contains("camera3D")) {
        json camera3DData = this->settingsData->at("camera3D");

        if (camera3DData.contains("x")) {
            camera3DSettings.position.x = camera3DData.at("x");
        }

        if (camera3DData.contains("y")) {
            camera3DSettings.position.y = camera3DData.at("y");
        }

        if (camera3DData.contains("z")) {
            camera3DSettings.position.z = camera3DData.at("z");
        }

        if (camera3DData.contains("targetX")) {
            camera3DSettings.target.x = camera3DData.at("targetX");
        }

        if (camera3DData.contains("targetY")) {
            camera3DSettings.target.y = camera3DData.at("targetY");
        }

        if (camera3DData.contains("targetZ")) {
            camera3DSettings.target.z = camera3DData.at("targetZ");
        }

        if (camera3DData.contains("upX")) {
            camera3DSettings.up.x = camera3DData.at("upX");
        }

        if (camera3DData.contains("upY")) {
            camera3DSettings.up.y = camera3DData.at("upY");
        }

        if (camera3DData.contains("upZ")) {
            camera3DSettings.up.z = camera3DData.at("upZ");
        }

        if (camera3DData.contains("fov")) {
            camera3DSettings.fov = camera3DData.at("fov");
        }
    }

    this->camera2D = new raylib::Camera2D(camera2DSettings.offset, camera2DSettings.position, camera2DSettings.rotation, camera2DSettings.zoom);
    this->camera3D = new raylib::Camera3D(camera3DSettings.position, camera3DSettings.target, camera3DSettings.up, camera3DSettings.fov, this->cameraProjectionMode);
}

Scene::~Scene() {}

void Scene::addActor(BaseActor* actor) {
    this->children.insert({actor->id, actor});
    this->baseContainer->addChildren(actor);
    this->signal_update.connect(actor->onUpdate);

    switch(actor->getActorRenderType()) {
        case ACTOR_2D:
            this->signal_render_2D.connect(actor->onRender);
        break;

        case ACTOR_3D:
            this->signal_render_3D.connect(actor->onRender);
        break;
    }
}

void Scene::removeActor(std::string id) {
    BaseActor* actor = this->children.at(id);

    this->children.erase(id);
    this->baseContainer->removeChildren(id);
    this->signal_update.disconnect(actor->onUpdate);

    switch(actor->getActorRenderType()) {
    case ACTOR_2D:
        this->signal_render_2D.disconnect(actor->onRender);
    break;

    case ACTOR_3D:
        this->signal_render_3D.disconnect(actor->onRender);
    break;
    }
}

BaseActor* Scene::getActorByID(std::string id) {
    return this->children.at(id);
}

void Scene::onUpdate(float dT) const {
    this->camera3D->Update(this->cameraProjectionMode);

    this->signal_update.emit(dT);
}

void Scene::onRender() const {
    this->camera3D->BeginMode();
        this->signal_render_3D.emit();
    this->camera3D->EndMode();

    if (this->use2DCamera) {
        this->camera2D->BeginMode();
            this->signal_render_2D.emit();
        this->camera2D->EndMode();
    } else {
        this->signal_render_2D.emit();
    }
}

void Scene::onInit() {}
void Scene::onEnter() {}
void Scene::onExit() {}
