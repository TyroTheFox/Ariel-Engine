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

    unsigned int occlusionTextureId;
    unsigned int specularTextureId;

    unsigned int depthRenderbufferId;
} GBufferData;

class GraphicsBuffer {
    private:
    public:
        int texUnitPosition = 0;
        int texUnitNormal = 1;
        int texUnitAlbedo = 2;
        int texUnitEmissive = 3;
        int texUnitMRA = 4;

        // int texUnitOcclusion = 5;
        // int texUnitSpecular = 6;

        GBufferData gBufferData;

        GraphicsBuffer();
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
        // void bindOcclusionTexture();
        // void bindSpecularTexture();

        void blitBuffer();

        void renderPostionTexture();
};

#endif