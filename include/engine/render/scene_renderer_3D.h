#pragma once

#ifndef SCENE_RENDERER_3D_H
#define SCENE_RENDERER_3D_H

#include <vector>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include "rlgl.h"
#include "raymath.h"

#include "engine/data/light.h"

#include <engine/render/rendering_shader.h>
#include <engine/render/gbuffer.h>

class SceneRenderer3D {
    private:        
        std::vector<Light*> lightList;
    public:
        RenderingShader* pbrShader;

        SceneRenderer3D();
        ~SceneRenderer3D();

        void createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, float intensity = 10.0f, raylib::Color color = raylib::Color::RayWhite());

        void setUpRenderer();
        void beginRender(raylib::Camera3D* camera);
        void endRenderAndProcess(raylib::Camera3D* camera);
};

#endif