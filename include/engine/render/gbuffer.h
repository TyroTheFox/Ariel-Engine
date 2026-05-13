#pragma once

#ifndef BUFFER_GRAPHICS_H
#define BUFFER_GRAPHICS_H

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/render/rendering_shader.h>
#include <engine/game/game_instance.h>

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

        GameInstance gameInstance;
    public:
        GraphicsBuffer(RenderingShader* deferredShader);
        ~GraphicsBuffer();

        void readyForDrawing();
        void enableColorBlending();
        void endBufferDrawing();

        void bindPositionTexture();
        void bindNormalTexture();
        void bindAlbedoTexture();

        void blitBuffer();
};

#endif