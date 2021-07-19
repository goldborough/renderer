#include "DepthBuffer.h"

DepthBuffer::DepthBuffer()
{
}

bool DepthBuffer::Init()
{
    glGenRenderbuffers(1, &m_bufferID);//rboDepth
    glBindRenderbuffer(GL_RENDERBUFFER, m_bufferID);//rboDepth
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_bufferID);//rboDepth
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

