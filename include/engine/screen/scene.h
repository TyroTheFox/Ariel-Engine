#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <nlohmann/json.hpp>

#include <engine/actors/actor_factory.h>

#include <engine/actors/base_actor.h>
#include <engine/actors/container.h>

#include <engine/render/scene_renderer_3D.h>

using json = nlohmann::json;

struct Camera2DSettings {
    Vector2 offset;
    Vector2 position;
    float rotation;
    float zoom;
};

struct Camera3DSettings {
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float fov;
};

class Scene
{
    protected:        
        std::map<std::string, BaseActor*> children;
        Container* baseContainer;
        
        raylib::Camera2D* camera2D;
        raylib::Camera3D* camera3D;
        
        bool use2DCamera = false;
        CameraProjection cameraProjectionMode = CAMERA_PERSPECTIVE;

        SceneRenderer3D* sceneRenderer3D;

        void setUpCameras();
    public:
        json* settingsData;
        json* actorData;
        
        std::string attachedStage;

        std::string id = "";
        sl::Signal<> actorAdded;
        sl::Signal<> actorRemoved;

        sl::Signal<float> signal_update;
        sl::Signal<> signal_render_2D;
        sl::Signal<> signal_render_3D;

        Scene();
        Scene(std::string id, json sceneData);
        ~Scene();

        void addActor(BaseActor* actor);
        void removeActor(std::string id);
        BaseActor* getActorByID(std::string id);

        raylib::Camera2D* getCamera2D();
        raylib::Camera3D* getCamera3D();

        virtual void onInit();
        virtual void onEnter();
        virtual void onExit();

        void onUpdate(float dT) const;
        void onRender() const;
};

#endif