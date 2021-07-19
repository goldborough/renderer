#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
    m_bufferID = 0;
}

bool FrameBuffer::Init()
{

    return true;
}

unsigned int FrameBuffer::GetBufferID()
{
    return m_bufferID;
}

void FrameBuffer::Bind()
{
    renderObject->BindFrameBuffer(m_bufferID);
}
