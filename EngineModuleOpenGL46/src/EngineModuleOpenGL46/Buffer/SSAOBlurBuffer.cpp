#include "SSAOBlurBuffer.h"

SSAOBlurBuffer::SSAOBlurBuffer()
{
}

bool SSAOBlurBuffer::Init()
{
    glGenFramebuffers(1, &m_bufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);

    glGenTextures(1, &m_textures.ssaoColorBufferBlur);
    glBindTexture(GL_TEXTURE_2D, m_textures.ssaoColorBufferBlur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures.ssaoColorBufferBlur, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void SSAOBlurBuffer::Begin()
{
    Bind();
    glClear(GL_COLOR_BUFFER_BIT);
}

void SSAOBlurBuffer::BeginTexture(unsigned int colorBuffer)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
}

SSAOBlurBufferTextures* SSAOBlurBuffer::GetTextures()
{
    return &m_textures;
}
