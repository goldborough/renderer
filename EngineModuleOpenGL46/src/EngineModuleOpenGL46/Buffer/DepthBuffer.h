#if !defined(DEPTHBUFFER_H)
#define DEPTHBUFFER_H

#include "FrameBuffer.h"

class DepthBuffer : public FrameBuffer
{
private:

public:
	DepthBuffer();

	bool Init() override;

};

#endif