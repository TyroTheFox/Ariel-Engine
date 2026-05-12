#pragma once

#ifndef BUFFER_GRAPHICS_H
#define BUFFER_GRAPHICS_H

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/render/shader.h>

typedef struct GBufferData {
    unsigned int framebufferId;

    unsigned int positionTextureId;
    unsigned int normalTextureId;
    unsigned int albedoSpecTextureId;

    unsigned int depthRenderbufferId;
} GBufferData;

// Deferred mode passes
typedef enum {
   DEFERRED_POSITION,
   DEFERRED_NORMAL,
   DEFERRED_ALBEDO,
   DEFERRED_SHADING
} DeferredMode;

class GraphicsBuffer {
    private:
        GBufferData gBufferData;
    public:
        GraphicsBuffer(RenderingShader* deferredShader, int screenWidth, int screenHeight);
        ~GraphicsBuffer();

        void readyForDrawing();
        void enableColorBlending();
        void endBufferDrawing();
};

#endif