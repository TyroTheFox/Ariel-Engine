#include <engine/screen/scene.h>

Scene::Scene() {
    this->id = "scene";
    this->baseContainer = new Container("scene_Container");
    this->children = std::map<std::string, BaseActor*>{};

    this->setUpCameras();

    this->sceneRenderer3D = new SceneRenderer3D();

    this->baseContainer->isBaseContainer = true; 
}

Scene::Scene(std::string name, json sceneData) {
    ActorFactory actorFactory = ActorFactory();

    this->id = name;
    this->baseContainer = new Container(name + "_Container");
    this->children = std::map<std::string, BaseActor*>{};

    this->settingsData = &sceneData.at("settings");
    this->actorData = &sceneData.at("actors");

    this->setUpCameras();

    this->baseContainer->isBaseContainer = true; 

    for (json entry : sceneData.at("actors")) {
        std::string actorId = entry.at("id");

        BaseActor* newActor = actorFactory.createActor(&entry);
        newActor->id = actorId;
        newActor->attachedScene = this;

        this->addActor(newActor);

        if (entry.contains("children")) {
            json childrenData = entry.at("children");

            for (auto& childData : childrenData) {
                auto newChild = actorFactory.createActor(&childData);
                newChild->id = actorId;
                newChild->attachedScene = this;
                static_cast<Container*>(newActor)->addChildren(newChild);
                this->addChildActor(newChild);
            }
        }
    }

    this->sceneRenderer3D = new SceneRenderer3D();

    if (sceneData.contains("lights")) {
        json lightData = sceneData.at("lights");

        for (json entry : lightData) {
            std::string lightId = entry.at("id");
            std::string lightType = entry.contains("type") ? entry.at("type") : "Directional";

            raylib::Vector3 lightPosition{ 0, 0, 0 };
            raylib::Vector3 lightTarget{ 0, 0, 0 };
            raylib::Color lightColor = raylib::Color::White();
            float lightIntensity = 5.0f;

            if (entry.contains("x")) {
                lightPosition.x = entry.at("x");
            }

            if (entry.contains("y")) {
                lightPosition.y = entry.at("y");
            }

            if (entry.contains("z")) {
                lightPosition.z = entry.at("z");
            }

            if (entry.contains("targetX")) {
                lightTarget.x = entry.at("x");
            }

            if (entry.contains("targetY")) {
                lightTarget.y = entry.at("y");
            }

            if (entry.contains("targetZ")) {
                lightTarget.z = entry.at("z");
            }

            if (entry.contains("intensity")) {
                lightIntensity = entry.at("intensity");
            }

            if (entry.contains("color")) {
                json colorData = entry.at("color");

                if (colorData.is_string()) {
                    lightColor = convertTextToColour(colorData.get<std::string>());
                }

                if (colorData.is_object()) {
                    lightColor = raylib::Color(
                        colorData.contains("r") ? colorData.at("r").get<char>() : 0,
                        colorData.contains("g") ? colorData.at("g").get<char>() : 0,
                        colorData.contains("b") ? colorData.at("b").get<char>() : 0,
                        colorData.contains("a") ? colorData.at("a").get<char>() : 255
                    );
                }
            }

            this->sceneRenderer3D->createNewLight(
                lightId,
                lightType == "Directional" ? LIGHT_DIRECTIONAL : LIGHT_POINT,
                lightPosition,
                lightTarget,
                lightIntensity,
                lightColor
            );
        }
    }

    this->sceneRenderer3D->setUpRenderer();
}

Scene::~Scene() {}

void Scene::setUpCameras() {
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

        case ACTOR_3D_BILLBOARD:
            this->signal_render_3D_BILLBOARD.connect(actor->onRender);
            this->signal_set_3D_BILLBOARD_RENDER_MODE.connect(dynamic_cast<BillboardSprite*>(actor)->onChangeRenderMode);
        break;

        case ACTOR_3D_OVER:
            this->signal_render_3D_OVER.connect(actor->onRender);
        break;
    }
}

void Scene::addChildActor(BaseActor* actor) {
    this->children.insert({actor->id, actor});
    this->signal_update.connect(actor->onUpdate);

    switch(actor->getActorRenderType()) {
        case ACTOR_2D:
            this->signal_render_2D.connect(actor->onRender);
        break;

        case ACTOR_3D:
            this->signal_render_3D.connect(actor->onRender);
        break;

        case ACTOR_3D_BILLBOARD:
            this->signal_render_3D_BILLBOARD.connect(actor->onRender);
            this->signal_set_3D_BILLBOARD_RENDER_MODE.connect(dynamic_cast<BillboardSprite*>(actor)->onChangeRenderMode);
        break;

        case ACTOR_3D_OVER:
            this->signal_render_3D_OVER.connect(actor->onRender);
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

        case ACTOR_3D_BILLBOARD:
            this->signal_render_3D_BILLBOARD.disconnect(actor->onRender);
            this->signal_set_3D_BILLBOARD_RENDER_MODE.disconnect(dynamic_cast<BillboardSprite*>(actor)->onChangeRenderMode);
        break;

        case ACTOR_3D_OVER:
            this->signal_render_3D_OVER.disconnect(actor->onRender);
        break;
    }
}

BaseActor* Scene::getActorByID(std::string id) {
    return this->children.at(id);
}

raylib::Camera2D* Scene::getCamera2D() {
    return this->camera2D;
}

raylib::Camera3D* Scene::getCamera3D() {
    return this->camera3D;
}

void Scene::onUpdate(float dT) const {
    this->camera3D->Update(this->cameraProjectionMode);

    this->signal_update.emit(dT);
}

void Scene::onRender() const {
    this->sceneRenderer3D->setUpLighting(this->camera3D);

    this->sceneRenderer3D->beginRenderModel(this->camera3D);
        this->sceneRenderer3D->readyBufferForDrawing();
        this->signal_render_3D.emit();
    this->sceneRenderer3D->endRenderModel(this->camera3D);
    
    this->sceneRenderer3D->beginRenderBillboard(this->camera3D);
        this->signal_render_3D_BILLBOARD.emit();
    this->sceneRenderer3D->endRenderBillboard(this->camera3D);

    this->sceneRenderer3D->processRender(this->camera3D);

    this->camera3D->BeginMode();
        this->signal_render_3D_OVER.emit();
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
