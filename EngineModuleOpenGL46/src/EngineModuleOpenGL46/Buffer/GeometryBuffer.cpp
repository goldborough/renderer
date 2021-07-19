#include "GeometryBuffer.h"

GeometryBuffer::GeometryBuffer()
    : m_textures(GeometryBufferTextures())
{

}

bool GeometryBuffer::Init()
{
    //unsigned int m_bufferID;
    glGenFramebuffers(1, &m_bufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);
    // position color buffer
    glGenTextures(1, &m_textures.gPosition);
    glBindTexture(GL_TEXTURE_2D, m_textures.gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textures.gPosition, 0);
    // normal color buffer
    glGenTextures(1, &m_textures.gNormal);
    glBindTexture(GL_TEXTURE_2D, m_textures.gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textures.gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &m_textures.gAlbedo);
    glBindTexture(GL_TEXTURE_2D, m_textures.gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_textures.gAlbedo, 0);
    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 

    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

	return true;
}

void GeometryBuffer::Begin()
{
   Bind();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GeometryBufferTextures* GeometryBuffer::GetTextures()
{
    return &m_textures;
}

