#if !defined(GEOMETRYBUFFER_H)
#define GEOMETRYBUFFER_H

#include "FrameBuffer.h"

struct GeometryBufferTextures
{
	unsigned int gPosition, gNormal, gAlbedo;

	GeometryBufferTextures() : gPosition(0), gNormal(0), gAlbedo(0) {}
};

class GeometryBuffer : public FrameBuffer
{
private:
	GeometryBufferTextures m_textures;

public:
	GeometryBuffer();

	bool Init() override;
	void Begin();

	GeometryBufferTextures * GetTextures();
};
#endif