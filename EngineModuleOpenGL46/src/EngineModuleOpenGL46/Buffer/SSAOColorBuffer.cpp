#include "SSAOColorBuffer.h"

SSAOColorBuffer::SSAOColorBuffer()
{
}

bool SSAOColorBuffer::Init()
{
    glGenFramebuffers(1, &m_bufferID);//ssaofbo
    glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID);//ssaofbo

    glGenTextures(1, &ssaoColorBuffer);
    glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "SSAO Framebuffer not complete!" << std::endl;
        return false;
    }

    std::uniform_real_distribution<GLfloat> randomFloats(0.0f, 1.0f); // generates random floats between 0.0 and 1.0
    std::default_random_engine generator;

    for (unsigned int i = 0; i < 64; ++i)
    {
        LMVector3 sample = LMVector3(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
        sample.Normalize();
        sample *= randomFloats(generator);
        float scale = float(i) / 64.0;

        // scale samples s.t. they're more aligned to center of kernel
        scale = MyMath::lerp(0.1f, 1.0f, scale * scale);
        sample *= scale;
        ssaoKernel.push_back(sample);
    }

    // generate noise texture
   // ----------------------
    for (unsigned int i = 0; i < 16; i++)
    {
        LMVector3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
        ssaoNoise.push_back(noise);
    }

    glGenTextures(1, &noiseTexture);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return true;
}

void SSAOColorBuffer::Begin()
{
    Bind();
    glClear(GL_COLOR_BUFFER_BIT);
}

void SSAOColorBuffer::BeginTextures(GeometryBufferTextures* geomTex)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, geomTex->gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, geomTex->gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);
}

std::vector<LMVector3>* SSAOColorBuffer::GetKernel()
{
    return &ssaoKernel;
}

std::vector<LMVector3>* SSAOColorBuffer::GetNoise()
{
    return &ssaoNoise;
}

unsigned int SSAOColorBuffer::GetColorBuffer()
{
    return ssaoColorBuffer;
}

unsigned int SSAOColorBuffer::GetNoiseTexture()
{
    return noiseTexture;
}
