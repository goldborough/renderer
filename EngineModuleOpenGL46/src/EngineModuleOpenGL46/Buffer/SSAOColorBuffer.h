#if !defined(SSAOCOLORBUFFER_H)
#define SSAOCOLORBUFFER_H

#include <random>

#include <EngineUtilities/Math.h>

#include "FrameBuffer.h"
#include "GeometryBuffer.h"

class SSAOColorBuffer : public FrameBuffer
{
private:
	unsigned int ssaoColorBuffer, noiseTexture;
	std::vector<LMVector3> ssaoKernel;
	std::vector<LMVector3> ssaoNoise;

public:
	SSAOColorBuffer();

	bool Init() override;

	void Begin();
	void BeginTextures(GeometryBufferTextures* geomTex);


	std::vector<LMVector3>* GetKernel();
	std::vector<LMVector3>* GetNoise();
	unsigned int GetColorBuffer();
	unsigned int GetNoiseTexture();

};
#endif