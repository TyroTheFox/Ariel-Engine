#include <engine/render/gbuffer_billboard.h>

GraphicsBufferBillboard::GraphicsBufferBillboard(RenderingShader* deferredShader) {
    // TODO: Recreate this for Billboards
    this->gBufferData = {0};
    this->gBufferData.framebufferId = ::rlLoadFramebuffer();
    if (this->gBufferData.framebufferId == 0) TraceLog(LOG_WARNING, "Failed to create framebufferId");

    // Enable Frame Buffer
    rlEnableFramebuffer(this->gBufferData.framebufferId);

    // Create Memory Areas for Textures
    this->gBufferData.positionTextureId = rlLoadTexture(NULL, SCREEN_WIDTH, SCREEN_HEIGHT, RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);
    this->gBufferData.normalTextureId = rlLoadTexture(NULL, SCREEN_WIDTH, SCREEN_HEIGHT, RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);
    this->gBufferData.albedoTextureId = rlLoadTexture(NULL, SCREEN_WIDTH, SCREEN_HEIGHT, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
    this->gBufferData.occlusionTextureId = rlLoadTexture(NULL, SCREEN_WIDTH, SCREEN_HEIGHT, RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);
    this->gBufferData.specularTextureId = rlLoadTexture(NULL, SCREEN_WIDTH, SCREEN_HEIGHT, RL_PIXELFORMAT_UNCOMPRESSED_R16G16B16, 1);
    
    // Set Active Draw Buffers
    ::rlActiveDrawBuffers(5);
    
    // Connect each rendered texture buffer to the main buffer ID
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.positionTextureId, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.normalTextureId, RL_ATTACHMENT_COLOR_CHANNEL1, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.albedoTextureId, RL_ATTACHMENT_COLOR_CHANNEL2, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.occlusionTextureId, RL_ATTACHMENT_COLOR_CHANNEL3, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.specularTextureId, RL_ATTACHMENT_COLOR_CHANNEL4, RL_ATTACHMENT_TEXTURE2D, 0);
    
    // Create Depth Buffer
    this->gBufferData.depthRenderbufferId = ::rlLoadTextureDepth(SCREEN_WIDTH, SCREEN_HEIGHT, true);
    rlFramebufferAttach(this->gBufferData.framebufferId, this->gBufferData.depthRenderbufferId, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);

    // Make sure our framebufferId is complete
    // NOTE: rlFramebufferComplete() automatically unbinds the framebufferId, so we don't have to rlDisableFramebuffer() here
    if (rlFramebufferComplete(this->gBufferData.framebufferId)) {
        TraceLog(LOG_INFO, "Framebuffer is complete");
    } else { 
        TraceLog(LOG_WARNING, "Framebuffer is NOT complete");
    }

    deferredShader->enableShader();
        int gPosition = rlGetLocationUniform(deferredShader->getID(), "gPosition");
        int gNormal = rlGetLocationUniform(deferredShader->getID(), "gNormal");
        int gAlbedo = rlGetLocationUniform(deferredShader->getID(), "gAlbedo");
        int gOcclusion = rlGetLocationUniform(deferredShader->getID(), "gOcclusion");
        int gSpecular = rlGetLocationUniform(deferredShader->getID(), "gSpecular");
        
        deferredShader->setShaderValue(gPosition, &this->texUnitPosition, RL_SHADER_UNIFORM_SAMPLER2D);
        deferredShader->setShaderValue(gNormal, &this->texUnitNormal, RL_SHADER_UNIFORM_SAMPLER2D);
        deferredShader->setShaderValue(gAlbedo, &this->texUnitAlbedo, RL_SHADER_UNIFORM_SAMPLER2D);
        deferredShader->setShaderValue(gOcclusion, &this->texUnitOcclusion, RL_SHADER_UNIFORM_SAMPLER2D);
        deferredShader->setShaderValue(gSpecular, &this->texUnitSpecular, RL_SHADER_UNIFORM_SAMPLER2D);
    deferredShader->disableShader();
}

GraphicsBufferBillboard::~GraphicsBufferBillboard()
{
    ::rlUnloadFramebuffer(this->gBufferData.framebufferId);

    ::rlUnloadTexture(this->gBufferData.positionTextureId);
    ::rlUnloadTexture(this->gBufferData.normalTextureId);
    ::rlUnloadTexture(this->gBufferData.albedoTextureId);
    ::rlUnloadTexture(this->gBufferData.occlusionTextureId);
    ::rlUnloadTexture(this->gBufferData.specularTextureId);

    ::rlUnloadTexture(this->gBufferData.depthRenderbufferId);
}

void GraphicsBufferBillboard::readyForDrawing() {
    ::rlEnableFramebuffer(this->gBufferData.framebufferId);
    ::rlClearColor(0, 0, 0, 0);
    ::rlClearScreenBuffers();  // Clear color and depth buffer
    ::rlDisableColorBlend();
}

void GraphicsBufferBillboard::enableColorBlending() {
    ::rlEnableColorBlend();
}

void GraphicsBufferBillboard::disableColorBlending() {
    ::rlDisableColorBlend();
}

void GraphicsBufferBillboard::endBufferDrawing() {
    ::rlDisableFramebuffer();
    ::rlClearScreenBuffers(); // Clear color & depth buffer
}

void GraphicsBufferBillboard::bindPositionTexture() {
    ::rlActiveTextureSlot(this->texUnitPosition);
    ::rlEnableTexture(this->gBufferData.positionTextureId);
}

void GraphicsBufferBillboard::bindNormalTexture() {
    ::rlActiveTextureSlot(this->texUnitNormal);
    ::rlEnableTexture(this->gBufferData.normalTextureId);
}

void GraphicsBufferBillboard::bindAlbedoTexture() {
    ::rlActiveTextureSlot(this->texUnitAlbedo);
    ::rlEnableTexture(this->gBufferData.albedoTextureId);
}

void GraphicsBufferBillboard::bindOcclusionTexture() {
    ::rlActiveTextureSlot(this->texUnitOcclusion);
    ::rlEnableTexture(this->gBufferData.occlusionTextureId);
}

void GraphicsBufferBillboard::bindSpecularTexture() {
    ::rlActiveTextureSlot(this->texUnitSpecular);
    ::rlEnableTexture(this->gBufferData.occlusionTextureId);
}

void GraphicsBufferBillboard::blitBuffer() {
    // As a last step, we now copy over the depth buffer from our g-buffer to the default framebufferId
    ::rlBindFramebuffer(RL_READ_FRAMEBUFFER, this->gBufferData.framebufferId);
    ::rlBindFramebuffer(RL_DRAW_FRAMEBUFFER, 0);
    ::rlBlitFramebuffer(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00000100); // GL_DEPTH_BUFFER_BIT
    ::rlDisableFramebuffer();
}