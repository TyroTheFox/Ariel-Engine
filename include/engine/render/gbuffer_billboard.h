#pragma once

#ifndef BUFFER_GRAPHICS_BILLBOARD_H
#define BUFFER_GRAPHICS_BILLBOARD_H

#include <engine/global_values.h>

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include "rlgl.h"
#include "raymath.h"

#include <engine/render/shader_objects/rendering_shader.h>

typedef struct GBufferBillboardData {
    unsigned int framebufferId;

    unsigned int positionTextureId;
    unsigned int normalTextureId;
    unsigned int albedoTextureId;
    unsigned int occlusionTextureId;
    unsigned int specularTextureId;

    unsigned int depthRenderbufferId;
} GBufferBillboardData;

class GraphicsBufferBillboard {
    private:
        int texUnitPosition = 0;
        int texUnitNormal = 1;
        int texUnitAlbedo = 2;
        int texUnitOcclusion = 3;
        int texUnitSpecular = 4;
    public:
        GBufferBillboardData gBufferData;

        GraphicsBufferBillboard(RenderingShader* deferredShader);
        ~GraphicsBufferBillboard();

        void readyForDrawing();
        void enableColorBlending();
        void disableColorBlending();
        void endBufferDrawing();

        void bindPositionTexture();
        void bindNormalTexture();
        void bindAlbedoTexture();
        void bindOcclusionTexture();
        void bindSpecularTexture();

        void blitBuffer();

        void renderPostionTexture();
};

#endif