#pragma once

#ifndef SCENE_RENDERER_BILLBOARD_H
#define SCENE_RENDERER_BILLBOARD_H

#include <vector>

#include <engine/global_values.h>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include "rlgl.h"
#include "raymath.h"

#include "engine/data/light.h"

#include <engine/render/shader_objects/shader_manager.h>
#include <engine/render/gbuffer_billboard.h>

class SceneRendererBillboard {
private:
    std::vector<Light> lightList;
public:
    raylib::Color ambientColor;

    GraphicsBufferBillboard* gBufferBillboard;

    RenderingShader* billboardShader;
    RenderingShader* billboardPosition;
    RenderingShader* billboardNormal;
    RenderingShader* gBuffer;
    RenderingShader* mixTexture;

    raylib::RenderTexture2D positionRenderTexture;
    raylib::RenderTexture2D albedoRenderTexture;
    raylib::RenderTexture2D normalRenderTexture;
    raylib::RenderTexture2D specularRenderTexture;
    raylib::RenderTexture2D occlusionRenderTexture;

    raylib::RenderTexture2D finalTexture;

    int texPositionLoc = -1;
    int texAlbedoLoc = -1;
    int texNormalLoc = -1;
    int texSpecularLoc = -1;
    int texOcclusionLoc = -1;

    raylib::Vector3 falloff;

    SceneRendererBillboard();
    ~SceneRendererBillboard();

    void createNewLight(std::string id, LightType type, raylib::Vector3 position, raylib::Vector3 target, float intensity = 10.0f, raylib::Color color = raylib::Color::RayWhite());

    void setUpRenderer();
    void setUpLights(raylib::Camera3D* camera);

    void beginPositionTextureRender(raylib::Camera3D* camera);
    void endPositionTextureRender(raylib::Camera3D* camera);
    
    void beginAlbedoTextureRender(raylib::Camera3D* camera);
    void endAlbedoTextureRender(raylib::Camera3D* camera);

    void beginNormalTextureRender(raylib::Camera3D* camera);
    void endNormalTextureRender(raylib::Camera3D* camera);

    void beginOcclusionTextureRender(raylib::Camera3D* camera);
    void endOcclusionTextureRender(raylib::Camera3D* camera);

    void beginSpecularTextureRender(raylib::Camera3D* camera);
    void endSpecularTextureRender(raylib::Camera3D* camera);

    void beginRender(raylib::Camera3D* camera);

    void endRender(raylib::Camera3D* camera);

    void processRender(raylib::Camera3D* camera);
};

#endif