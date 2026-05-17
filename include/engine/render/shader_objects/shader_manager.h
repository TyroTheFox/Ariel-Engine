#pragma once

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <map>
#include <unordered_map>

#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <engine/utility/json_handler.h>

#include <engine/render/shader_objects/rendering_shader.h>

class ShaderManager
{
private:
    static std::map<std::string, RenderingShader*> shaderCache;

    static std::string defaultShader;

    static std::unordered_map<std::string, int> shaderLocationIndexes;
public:
    ShaderManager();
    ~ShaderManager();

    void loadManifest(json jsonData);

    void unloadCurrentManifest();

    int convertStringToShaderLocationIndex(std::string indexName);

    RenderingShader* getShaderPtr(std::string shaderID);
    RenderingShader* getDefaultShaderPtr();
};

#endif