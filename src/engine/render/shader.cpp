#include <engine/render/shader.h>

RenderingShader::RenderingShader(std::string vertexPath, std::string fragmentPath) {
    this->shaderInstance = raylib::Shader(TextFormat(vertexPath.c_str(), GLSL_VERSION), TextFormat(fragmentPath.c_str(), GLSL_VERSION));
}

RenderingShader::~RenderingShader() {
}

void RenderingShader::setShaderLocation(ShaderLocationIndex index, std::string uniformName) {
    this->shaderInstance.locs[index] = GetShaderLocation(this->shaderInstance, uniformName.c_str());
}

unsigned int RenderingShader::getID() {
    return this->shaderInstance.id;
}

void RenderingShader::enableShader() {
    rlEnableShader(this->shaderInstance.id);
}

void RenderingShader::disableShader() {
    rlDisableShader();
}