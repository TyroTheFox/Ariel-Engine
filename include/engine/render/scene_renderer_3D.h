#pragma once

#ifndef SCENE_RENDERER_3D_H
#define SCENE_RENDERER_3D_H

#include <vector>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#define RLIGHTS_IMPLEMENTATION
#include "engine/data/light.h"

#include <engine/render/rendering_shader.h>
#include <engine/render/gbuffer.h>
#include <engine/screen/scene.h>

// Deferred mode passes
typedef enum {
   DEFERRED_POSITION,
   DEFERRED_NORMAL,
   DEFERRED_ALBEDO,
   DEFERRED_SHADING
} DeferredMode;

class SceneRenderer3D {
    private:
        GraphicsBuffer* gBufferInstance;
        
        std::vector<Light*> lightList;

        DeferredMode currentMode;
    public:
        RenderingShader* deferredShader;
        RenderingShader* gBufferShader;

        SceneRenderer3D();
        ~SceneRenderer3D();

        void createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, raylib::Color color);
        void render(raylib::Camera3D* camera, const Scene* renderedScene);
};

#endif