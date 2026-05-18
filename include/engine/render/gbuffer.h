#pragma once

#ifndef BUFFER_GRAPHICS_H
#define BUFFER_GRAPHICS_H

#include <engine/global_values.h>

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include "rlgl.h"
#include "raymath.h"

#include <engine/render/shader_objects/rendering_shader.h>

typedef struct GBufferData {
    unsigned int framebufferId;

    unsigned int positionTextureId;
    unsigned int normalTextureId;
    unsigned int albedoTextureId;
    unsigned int emissiveTextureId;
    unsigned int MRATextureID;

    unsigned int depthRenderbufferId;
} GBufferData;

class GraphicsBuffer {
    private:
        GBufferData gBufferData;

        int texUnitPosition = 0;
        int texUnitNormal = 1;
        int texUnitAlbedo = 2;
        int texUnitEmissive = 3;
        int texUnitMRA = 4;
    public:
        GraphicsBuffer(RenderingShader* deferredShader);
        ~GraphicsBuffer();

        void readyForDrawing();
        void enableColorBlending();
        void disableColorBlending();
        void endBufferDrawing();

        void bindPositionTexture();
        void bindNormalTexture();
        void bindAlbedoTexture();
        void bindEmissiveTexture();
        void bindMRATexture();

        void blitBuffer();
};

#endif