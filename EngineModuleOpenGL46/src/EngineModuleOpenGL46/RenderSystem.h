#if !defined(RENDERSYSTEM_H)
#define RENDERSYSTEM_H

#include <vector>
using std::vector;
#include <map>
using std::map;
#include <iostream>
#include <functional>
using namespace std::placeholders;

#include <EngineUtilities/Util.h>
#include <EngineUtilities/View/camera.h>

#include "Subsystem/AmbientOcclusionSubsystem.h"
#include "Model/RenderQuad.h"
#include "RenderObject.h"
#include "ObjectView.h"

enum SubsystemID
{
	SYSAmbientOcculusion,
};

enum RenderMethodology
{
	methodLightAO,
	renderMethodologyCount
};

struct RenderConfiguration
{
	RenderMethodology m_id;
	//color information
	//performance
	//lod
};

enum RenderSystemState
{
	renderSystemActive,
	renderSystemInactive
};

class RenderSystem
{
private:
	map<SystemComponentType, std::function<SystemComponent*()>> m_objectCreator;
	map<SystemComponentType, SystemComponent*> m_componentMap;

	map<ShaderNames, std::function<Shader()>> m_shaderObjectCreator;
	map<ShaderNames, Shader* > m_shaderComponentMap;

	vector<BaseSubsystem*> m_allSubsystemInstances;
	vector<BaseSubsystem*> m_renderPassVector;

	vector<ObjectView*> * m_objectViews;

	RenderObject* m_renderObject;

	Camera m_camera; //make camera controller

	Primitive * m_quad;

	LMVector2 m_nextDimensions;

	RenderSystemState m_state;
	int m_currentSubsystemIndex;
	int m_subsystemCount;

	BaseSubsystem* m_currentSubsystem;

	//Render2() Variables

	AmbientOcclusionSubsystem* m_ao;//debug only

public:


	RenderSystem();
	~RenderSystem();

	bool Init(const RenderConfiguration& config);
	void Render2();
	
	void BeginRender();
	void EndRender();

	bool IsActive();

	void Advance();
	
	void SetObjects(vector<ObjectView*>* objectViews);
	void Draw();

	void Resize(int width, int height);

	void SetRenderObject(RenderObject& renderObject);

private:
	bool SubsystemCanAdvance();
	void SubsystemAdvance();
	bool RenderSystemCanAdvance();
	void RenderSystemAdvance();

};
#endif