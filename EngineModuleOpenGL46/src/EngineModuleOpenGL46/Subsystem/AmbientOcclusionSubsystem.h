#if !defined(AMBIENTOCCULSIONSYSTEM_H)
#define AMBIENTOCCULSIONSYSTEM_H

#include <EngineUtilities/Util.h>

#include <EngineModuleOpenGL46/Buffer/GeometryBuffer.h>
#include <EngineModuleOpenGL46/Buffer/DepthBuffer.h>
#include <EngineModuleOpenGL46/Buffer/SSAOColorBuffer.h>
#include <EngineModuleOpenGL46/Buffer/SSAOBlurBuffer.h>
#include <EngineModuleOpenGL46/Shader/Shader.h>
#include <EngineModuleOpenGL46/ObjectView.h>

#include "BaseSubsystem.h"

enum AmbientOcclusionSubsystemState
{
	AOSYSgeometryPass,
	AOSYSgenerateSSAOTexturePass,
	AOSYSblurSSAOTexturePass,
	AOSYSlightingpass
};

class AmbientOcclusionSubsystem : public BaseSubsystem
{	
private:
	GeometryBuffer* m_geometryBuffer;
	DepthBuffer* m_depthBuffer;
	SSAOColorBuffer* m_ssaoColorBuffer;
	SSAOBlurBuffer* m_ssaoBlurBuffer;

	Shader * m_shader;


	LMMatrix4 projection;
	LMMatrix4 view;

	GeometryBufferTextures * m_geomTextures;
	SSAOBlurBufferTextures* m_ssaoblurTextures;

	LMVector3 m_lightPos;
	LMVector3 m_lightColor;
	LMVector3 m_lightPosView;
	float m_linear;
	float m_quadratic;

public:
	AmbientOcclusionSubsystem();
	virtual bool Init(const std::map<SystemComponentType, SystemComponent*>& map, const std::map< ShaderNames, Shader* >& shadermap) final;
	virtual void Update(float deltaTime) final;//todo remove if not needed

	void Activate() override;
	void Deactivate() override;

	virtual bool CanAdvance() final;
	virtual void Advance() final;
	virtual void Draw(vector<ObjectView*>* objectViews) final;

//private:
	void OnEnterGeometry();
	void GeometryDraw();
	void OnExitGeometry();

	void OnEnterSSAOTexturePass();
	void SSAOTextureDraw();
	void OnExitSSAOTexturePass();

	void OnEnterSSAOTextureBlurPass();
	void SSAOTextureBlurDraw();
	void OnExitSSAOTextureBlurPass();

	void OnEnterLightingPass();
	void LightingDraw();
	void OnExitLightingPass();

	virtual void OnEnterActive() override final;
	virtual void ActiveBehavior() override final;
	virtual void OnExitActive() override final;

	virtual void OnEnterInactive() final;
	virtual void InactiveBehavior() final;//todo remove if not needed
	virtual void OnExitInactive() final;

};
#endif