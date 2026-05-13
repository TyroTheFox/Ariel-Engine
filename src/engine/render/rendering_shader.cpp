#include <engine/render/rendering_shader.h>

RenderingShader::RenderingShader(std::string vertexPath, std::string fragmentPath) {
    this->shaderInstance = raylib::Shader(::TextFormat(vertexPath.c_str(), GLSL_VERSION), ::TextFormat(fragmentPath.c_str(), GLSL_VERSION));
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
    this->shaderInstance.locs[index] = ::GetShaderLocation(this->shaderInstance, uniformName.c_str());
}

int RenderingShader::getShaderLocation(ShaderLocationIndex index) {
    return this->shaderInstance.locs[index];
}

void RenderingShader::setShaderValue(std::string locationName, int usage, int uniformType) {
    ::SetShaderValue(this->shaderInstance, ::GetShaderLocation(this->shaderInstance, locationName.c_str()), &usage, uniformType);
}

void RenderingShader::setShaderValue(int locIndex, const void *value, int uniformType) {
    ::SetShaderValue(this->shaderInstance, locIndex, value, uniformType);
}

void RenderingShader::setShaderValueV(int locIndex, const void *value, int uniformType, int count) {
    ::SetShaderValueV(this->shaderInstance, locIndex, value, uniformType, count);
}

void RenderingShader::setShaderMatrixValue(int locIndex, Matrix mat) {
    ::SetShaderValueMatrix(this->shaderInstance, locIndex, mat);
}

void RenderingShader::setShaderTextureValue(int locIndex, Texture2D texture) {
    ::SetShaderValueTexture(this->shaderInstance, locIndex, texture);
}
