#if !defined(FRAMEBUFFER_H)
#define FRAMEBUFFER_H

#include <EngineModuleOpenGL46/RenderInterface.h>
#include <EngineModuleOpenGL46/SystemComponent.h>

class FrameBuffer : public RenderInterface, public SystemComponent
{

protected:
	unsigned int m_bufferID;

public:
	FrameBuffer();
	bool Init();

	unsigned int GetBufferID();
	void Bind();


};

#endif