#pragma once

#ifndef SCENE_RENDERER_3D_H
#define SCENE_RENDERER_3D_H

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/render/shader.h>
#include <engine/render/gbuffer.h>

class SceneRenderer3D
{
private:
    GraphicsBuffer* gBufferInstance;

    RenderingShader* defferredShader;
    RenderingShader* gBufferShader;
public:
    SceneRenderer3D(int screenWidth, int screenHeight);
    ~SceneRenderer3D();
};

#endif