#include "AmbientOcclusionSubsystem.h"


/*
	GeometryBuffer* pGeo = new GeometryBuffer();
	SystemComponent* pComp = pGeo;
	GeometryBuffer** ppGeo = &pGeo;
	SystemComponent** ppComp = &pComp;

	std::vector<SystemComponent**> vec;
	vec.push_back(ppGeo);
	
	//m_components.at(SysCompGeometryBuffer);

	//m_geometryBuffer = nullptr;
	//m_geometryBuffer = (GeometryBuffer*)m_components.at(SysCompGeometryBuffer);
*/

AmbientOcclusionSubsystem::AmbientOcclusionSubsystem()
{
	m_recipe.push_back(SysCompGeometryBuffer);
	m_recipe.push_back(SysCompDepthBuffer);
	m_recipe.push_back(SysCompSSAOColorBuffer);
	m_recipe.push_back(SysCompSSAOBlurBuffer);
	m_components.resize(m_recipe.size());

	m_shaderRecipe.push_back(shaderGeometryPass);
	m_shaderRecipe.push_back(shaderLightingPass);
	m_shaderRecipe.push_back(shaderSSAO);
	m_shaderRecipe.push_back(shaderSSAOBlur);
	m_shaders.resize(m_shaderRecipe.size());

	m_OnEnterForState.insert({ AOSYSgeometryPass , std::bind(&AmbientOcclusionSubsystem::OnEnterGeometry, this) });
	m_OnEnterForState.insert({ AOSYSgenerateSSAOTexturePass , std::bind(&AmbientOcclusionSubsystem::OnEnterSSAOTexturePass, this) });
	m_OnEnterForState.insert({ AOSYSblurSSAOTexturePass , std::bind(&AmbientOcclusionSubsystem::OnEnterSSAOTextureBlurPass, this) });
	m_OnEnterForState.insert({ AOSYSlightingpass , std::bind(&AmbientOcclusionSubsystem::OnEnterLightingPass, this) });

	m_OnExitForState.insert({ AOSYSgeometryPass , std::bind(&AmbientOcclusionSubsystem::OnExitGeometry, this) });
	m_OnExitForState.insert({ AOSYSgenerateSSAOTexturePass , std::bind(&AmbientOcclusionSubsystem::OnExitSSAOTexturePass, this) });
	m_OnExitForState.insert({ AOSYSblurSSAOTexturePass , std::bind(&AmbientOcclusionSubsystem::OnExitSSAOTextureBlurPass, this) });
	m_OnExitForState.insert({ AOSYSlightingpass , std::bind(&AmbientOcclusionSubsystem::OnExitLightingPass, this) });

	m_DrawForState.insert({ AOSYSgeometryPass , std::bind(&AmbientOcclusionSubsystem::GeometryDraw, this) });
	m_DrawForState.insert({ AOSYSgenerateSSAOTexturePass , std::bind(&AmbientOcclusionSubsystem::SSAOTextureDraw, this) });
	m_DrawForState.insert({ AOSYSblurSSAOTexturePass , std::bind(&AmbientOcclusionSubsystem::SSAOTextureBlurDraw, this) });
	m_DrawForState.insert({ AOSYSlightingpass , std::bind(&AmbientOcclusionSubsystem::LightingDraw, this) });

	m_stateCount = m_recipe.size();
}

/*
*
* Could use these for clarity:
* SystemComponent* component = p.second;
* GeometryBuffer * b = (GeometryBuffer*) p.second;

	std::pair<const SystemComponentType, SystemComponent*> p = *map.find(SysCompGeometryBuffer);
	m_components.at(0) = p.second;
	bool result = m_components.at(0)->Init();

	std::pair<const ShaderNames, Shader*> s = *shadermap.find(shaderGeometryPass);
	m_shaders.at(0) = s.second;
	result = m_shaders.at(0)->Init();

*/

bool AmbientOcclusionSubsystem::Init(const std::map<SystemComponentType, SystemComponent*>& map, const std::map< ShaderNames, Shader* >& shadermap)
{
	//for loop recipe
	for (unsigned int i = 0; i < m_recipe.size(); i++)
	{
		std::pair<const SystemComponentType, SystemComponent*> p = *map.find(m_recipe.at(i));
		m_components.at(i) = p.second;
		
		if (!m_components.at(i)->Init())
		{
			DebugPrint("Unable to init component");
			return false;
		}
	}

	//for loop shader (move to base class?)
	for (unsigned int i = 0; i < m_shaderRecipe.size(); i++)
	{
		std::pair<const ShaderNames, Shader*> s = *shadermap.find(m_shaderRecipe.at(i));
		m_shaders.at(i) = s.second;

		if (!m_shaders.at(i)->Init())
		{
			DebugPrint("Unable to init shader");
			return false;
		}
	}

	m_geometryBuffer = (GeometryBuffer*)(*map.find(SysCompGeometryBuffer)).second;
	m_depthBuffer = (DepthBuffer*)(*map.find(SysCompDepthBuffer)).second;
	m_ssaoColorBuffer = (SSAOColorBuffer*)(*map.find(SysCompSSAOColorBuffer)).second;
	m_ssaoBlurBuffer = (SSAOBlurBuffer*)(*map.find(SysCompSSAOBlurBuffer)).second;

	m_quad = (RenderQuad*)(*map.find(SysCompRenderQuad)).second;

	m_shaders.at(shaderLightingPass)->use();
	m_shaders.at(shaderLightingPass)->setInt("gPosition", 0);
	m_shaders.at(shaderLightingPass)->setInt("gNormal", 1);
	m_shaders.at(shaderLightingPass)->setInt("gAlbedo", 2);
	m_shaders.at(shaderLightingPass)->setInt("ssao", 3);
	m_shaders.at(shaderSSAO)->use();
	m_shaders.at(shaderSSAO)->setInt("gPosition", 0);
	m_shaders.at(shaderSSAO)->setInt("gNormal", 1);
	m_shaders.at(shaderSSAO)->setInt("texNoise", 2);
	m_shaders.at(shaderSSAOBlur)->use();
	m_shaders.at(shaderSSAOBlur)->setInt("ssaoInput", 0);

	m_lightPos = LMVector3(2.0, 4.0, -2.0);//todo remove
	m_lightColor = LMVector3(0.55, 0.55, 0.55);

	m_linear = 0.09;
	m_quadratic = 0.032;

	return true;
}

void AmbientOcclusionSubsystem::Update(float deltaTime)
{
	
}

void AmbientOcclusionSubsystem::Activate()
{
	DebugPrint("AmbientOcclusionSubsystem::Activate()");

	OnExitInactive();
	OnEnterActive();
}

void AmbientOcclusionSubsystem::Deactivate()
{
	SubsystemOnExitForState(m_currentState);
	OnExitActive();
	OnEnterInactive();
}

void AmbientOcclusionSubsystem::Advance()
{
	SubsystemOnExitForState(m_currentState);
	m_currentState++;
	SubsystemOnEnterForState(m_currentState);
}

bool AmbientOcclusionSubsystem::CanAdvance()
{
	return (m_currentState + 1 <= m_stateCount - 1) ? true : false;
}

void AmbientOcclusionSubsystem::Draw(vector<ObjectView*>* objectViews)
{
	DebugPrint("AmbientOcclusionSubsystem::Draw");
	m_objectViews = objectViews;

	SubsystemDrawForState(m_currentState);
}

void AmbientOcclusionSubsystem::OnEnterActive()
{
	m_subsystemState = subsystemActive;
	m_currentState = AOSYSgeometryPass;
	SubsystemOnEnterForState(m_currentState);

	m_geomTextures = m_geometryBuffer->GetTextures();
	m_ssaoblurTextures = m_ssaoBlurBuffer->GetTextures();
}

void AmbientOcclusionSubsystem::OnExitActive()
{
	
}

void AmbientOcclusionSubsystem::OnEnterInactive()
{
	m_subsystemState = subsystemInactive;
}

void AmbientOcclusionSubsystem::OnExitInactive()
{
	
}

void AmbientOcclusionSubsystem::ActiveBehavior()
{
	// Update behaviors not needed yet
}

void AmbientOcclusionSubsystem::InactiveBehavior()
{
	// Update behaviors not needed yet
}

void AmbientOcclusionSubsystem::OnEnterGeometry()
{
	DebugPrint("1");
	m_currentState = AOSYSgeometryPass;
	m_shader = m_shaders.at(shaderGeometryPass);

	m_geometryBuffer->Begin();

	projection = MyMath::BuildPerspectiveFovRHMatrix(MyMath::radians(m_camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
	view = m_camera->GetViewMatrix();

	m_shaders.at(shaderGeometryPass)->use();
	m_shaders.at(shaderGeometryPass)->setMat4("projection", projection);
	m_shaders.at(shaderGeometryPass)->setMat4("view", view);
}

void AmbientOcclusionSubsystem::GeometryDraw()
{
	DebugPrint("2");
	for (unsigned int i = 0; i < m_objectViews->size(); i++)
	{
		Property prop = Property("visible", 0);
		LMMatrix4 model = *m_objectViews->at(i)->GetModelMatrix();

		m_shader->setMat4("model", model);
		
		if (!m_objectViews->at(i)->FindProperty(&prop))
		{
			if (prop.m_fieldValue == 0) continue;
		}

		prop = Property("invertNormals", 0);
		m_shader->setInt("invertedNormals", 0);

		if (m_objectViews->at(i)->FindProperty(&prop))
		{
			if (prop.m_fieldValue == 1)
			{
				m_shader->setInt("invertedNormals", 1);
			}
		}

		m_objectViews->at(i)->Draw(*m_shader);
		m_shader->setInt("invertedNormals", 0);
	}
}

void AmbientOcclusionSubsystem::OnExitGeometry()
{
	DebugPrint("3");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void AmbientOcclusionSubsystem::OnEnterSSAOTexturePass()
{
	DebugPrint("4");
	m_currentState = AOSYSgenerateSSAOTexturePass;
	m_shader = m_shaders.at(shaderSSAO);

	m_ssaoColorBuffer->Begin();
	m_shaders.at(shaderSSAO)->use();

	std::vector<LMVector3>* ssaoKernel = m_ssaoColorBuffer->GetKernel();
	for (unsigned int i = 0; i < 64; ++i)
	{
		m_shaders.at(shaderSSAO)->setVec3("samples[" + std::to_string(i) + "]", (*ssaoKernel)[i]);
	}

	m_shaders.at(shaderSSAO)->setMat4("projection", projection);
	m_ssaoColorBuffer->BeginTextures(m_geomTextures);
}

void AmbientOcclusionSubsystem::SSAOTextureDraw()
{
	DebugPrint("5");
	m_quad->Draw(*m_shaders.at(shaderSSAO));
}

void AmbientOcclusionSubsystem::OnExitSSAOTexturePass()
{
	DebugPrint("6");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void AmbientOcclusionSubsystem::OnEnterSSAOTextureBlurPass()
{
	DebugPrint("7");
	m_currentState = AOSYSblurSSAOTexturePass;
	m_shader = m_shaders.at(shaderSSAOBlur);
	m_ssaoBlurBuffer->Begin();
	m_shader->use();
	m_ssaoBlurBuffer->BeginTexture(m_ssaoColorBuffer->GetColorBuffer());
}

void AmbientOcclusionSubsystem::SSAOTextureBlurDraw()
{
	DebugPrint("8");
	m_quad->Draw(*m_shaders.at(shaderSSAOBlur));
}

void AmbientOcclusionSubsystem::OnExitSSAOTextureBlurPass()
{
	DebugPrint("9");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void AmbientOcclusionSubsystem::OnEnterLightingPass()
{
	DebugPrint("10");
	m_currentState = AOSYSlightingpass;
	m_shader = m_shaders.at(shaderLightingPass);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shaders.at(shaderLightingPass)->use();
	m_lightPosView = MyMath::Vec4ToVec3(m_camera->GetViewMatrix() * LMVector4(m_lightPos, 1.0f));

	m_shaders.at(shaderLightingPass)->setVec3("light.Position", m_lightPosView);
	m_shaders.at(shaderLightingPass)->setVec3("light.Color", m_lightColor);
	m_shaders.at(shaderLightingPass)->setFloat("light.Linear", m_linear);
	m_shaders.at(shaderLightingPass)->setFloat("light.Quadratic", m_quadratic);

	//todo make textures class
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_geomTextures->gPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_geomTextures->gNormal);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_geomTextures->gAlbedo);
	glActiveTexture(GL_TEXTURE3); // add extra SSAO texture to lighting pass
	glBindTexture(GL_TEXTURE_2D, m_ssaoblurTextures->ssaoColorBufferBlur);

}

void AmbientOcclusionSubsystem::LightingDraw()
{
	DebugPrint("11");
	m_quad->Draw(*m_shaders.at(shaderLightingPass));
}

void AmbientOcclusionSubsystem::OnExitLightingPass()
{
	DebugPrint("12");
	OnExitActive();
	OnEnterInactive();
}
