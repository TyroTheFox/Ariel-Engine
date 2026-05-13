#pragma once

#ifndef BUFFER_GRAPHICS_H
#define BUFFER_GRAPHICS_H

#include <engine/global_values.h>

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include "rlgl.h"
#include "raymath.h"

#include <engine/render/rendering_shader.h>

typedef struct GBufferData {
    unsigned int framebufferId;

    unsigned int positionTextureId;
    unsigned int normalTextureId;
    unsigned int albedoSpecTextureId;

    unsigned int depthRenderbufferId;
} GBufferData;

class GraphicsBuffer {
    private:
        GBufferData gBufferData;

        int texUnitPosition = 0;
        int texUnitNormal = 1;
        int texUnitAlbedoSpec = 2;
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

        void blitBuffer();
};

#endif