#include <engine/render/gbuffer.h>

GraphicsBuffer::GraphicsBuffer(RenderingShader* deferredShader, int screenWidth, int screenHeight) {
    this->gBufferData = {0};
    this->gBufferData.framebufferId = rlLoadFramebuffer();
    if (this->gBufferData.framebufferId == 0) TraceLog(LOG_WARNING, "Failed to create framebufferId");

    // Enable Frame Buffer
    rlEnableFramebuffer(this->gBufferData.framebufferId);

    // Create Memory Areas for Textures
    this->gBufferData.positionTextureId = rlLoadTexture(NULL, screenWidth, screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);
    this->gBufferData.normalTextureId = rlLoadTexture(NULL, screenWidth, screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);
    this->gBufferData.albedoSpecTextureId = rlLoadTexture(NULL, screenWidth, screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);

    // Set Active Draw Buffers
    rlActiveDrawBuffers(3);

    // Connect each rendered texture buffer to the main buffer ID
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.positionTextureId, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.normalTextureId, RL_ATTACHMENT_COLOR_CHANNEL1, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.albedoSpecTextureId, RL_ATTACHMENT_COLOR_CHANNEL2, RL_ATTACHMENT_TEXTURE2D, 0);

    // Create Depth Buffer
    this->gBufferData.depthRenderbufferId = rlLoadTextureDepth(screenWidth, screenHeight, true);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.depthRenderbufferId, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);

    // Make sure our framebufferId is complete
    // NOTE: rlFramebufferComplete() automatically unbinds the framebufferId, so we don't have to rlDisableFramebuffer() here
    if (!rlFramebufferComplete(this->gBufferData.framebufferId)) TraceLog(LOG_WARNING, "Framebuffer is not complete");

    rlEnableShader(deferredShader->getID());
    int texUnitPosition = 0;
    int texUnitNormal = 1;
    int texUnitAlbedoSpec = 2;
    SetShaderValue(deferredShader->shaderInstance, rlGetLocationUniform(deferredShader->getID(), "gPosition"), &texUnitPosition, RL_SHADER_UNIFORM_SAMPLER2D);
    SetShaderValue(deferredShader->shaderInstance, rlGetLocationUniform(deferredShader->getID(), "gNormal"), &texUnitNormal, RL_SHADER_UNIFORM_SAMPLER2D);
    SetShaderValue(deferredShader->shaderInstance, rlGetLocationUniform(deferredShader->getID(), "gAlbedoSpec"), &texUnitAlbedoSpec, RL_SHADER_UNIFORM_SAMPLER2D);
    rlDisableShader();
}

GraphicsBuffer::~GraphicsBuffer()
{
    rlUnloadFramebuffer(this->gBufferData.framebufferId);
    rlUnloadTexture(this->gBufferData.positionTextureId);
    rlUnloadTexture(this->gBufferData.normalTextureId);
    rlUnloadTexture(this->gBufferData.albedoSpecTextureId);
    rlUnloadTexture(this->gBufferData.depthRenderbufferId);
}

void GraphicsBuffer::readyForDrawing() {
    rlEnableFramebuffer(this->gBufferData.framebufferId);
    rlClearColor(0, 0, 0, 0);
    rlClearScreenBuffers();  // Clear color and depth buffer
    rlDisableColorBlend();
}

void GraphicsBuffer::enableColorBlending() {
    rlEnableColorBlend();
}

void GraphicsBuffer::endBufferDrawing() {
    rlDisableFramebuffer();
    rlClearScreenBuffers(); // Clear color & depth buffer
}

