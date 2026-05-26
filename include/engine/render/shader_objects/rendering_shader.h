#pragma once

#ifndef RENDERING_SHADER_H
#define RENDERING_SHADER_H

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            120
#endif

#include <string>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

class RenderingShader {
    private:
    public:
        raylib::Shader shaderInstance;
        RenderingShader(std::string vertexPath = "", std::string fragmentPath = "");
        ~RenderingShader();

        void rlEnableShader();
        void rlDisableShader();
        void enableShader();
        void disableShader();

        unsigned int getID();

        void setShaderLocation(int index, std::string uniformName);
        int getShaderLocation(int index);
        int getShaderLocation(std::string location);

        void setShaderValue(std::string locationName, const void *value, int uniformType);
        void setShaderValue(int locIndex, const void *value, int uniformType);
        void setShaderValueV(int locIndex, const void *value, int uniformType, int count);
        void setShaderMatrixValue(int locIndex, Matrix mat);
        void setShaderTextureValue(int locIndex, Texture2D texture);
};

#endif