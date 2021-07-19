#if !defined(SSAOBLURBUFFER_H)
#define SSAOBLURBUFFER_H

#include <random>
#include <EngineUtilities/Math.h>
#include "FrameBuffer.h"

struct SSAOBlurBufferTextures
{
	unsigned int ssaoColorBufferBlur;

	SSAOBlurBufferTextures() : ssaoColorBufferBlur(0) {}
};



class SSAOBlurBuffer : public FrameBuffer
{
private:
	SSAOBlurBufferTextures m_textures;

public:
	SSAOBlurBuffer();

	bool Init() override;
	void Begin();
	void BeginTexture(unsigned int colorBuffer);

	SSAOBlurBufferTextures* GetTextures();

};

#endif