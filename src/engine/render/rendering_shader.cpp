#include <engine/render/rendering_shader.h>

RenderingShader::RenderingShader(std::string vertexPath, std::string fragmentPath) {
    this->shaderInstance = raylib::Shader(TextFormat(vertexPath.c_str(), GLSL_VERSION), TextFormat(fragmentPath.c_str(), GLSL_VERSION));
}

RenderingShader::~RenderingShader() {
    UnloadShader(this->shaderInstance);
}

void RenderingShader::enableShader() {
    rlEnableShader(this->shaderInstance.id);
}

void RenderingShader::disableShader() {
    rlDisableShader();
}

unsigned int RenderingShader::getID() {
    return this->shaderInstance.id;
}

void RenderingShader::setShaderLocation(ShaderLocationIndex index, std::string uniformName) {
    this->shaderInstance.locs[index] = GetShaderLocation(this->shaderInstance, uniformName.c_str());
}

void RenderingShader::setShaderValue(raylib::Shader shader, std::string locationName, int usage, int uniformType) {
     SetShaderValue(shader, GetShaderLocation(shader, locationName.c_str()), &usage, uniformType);
}
