#if !defined(BASESUBSYSTEM_H)
#define BASESUBSYSTEM_H

#include <map>
#include <vector>

enum SubsystemState
{
	subsystemActive,
	subsystemInactive
};

enum SystemComponentType
{
	SysCompRenderQuad,
	SysCompGeometryBuffer,
	SysCompDepthBuffer,
	SysCompSSAOColorBuffer,
	SysCompSSAOBlurBuffer,
	SysCompCount
};


//possibly make shadernames a constexpr list
//#define 
enum ShaderNames
{
	shaderGeometryPass,
	shaderLightingPass,
	shaderSSAO,
	shaderSSAOBlur,
	shaderNamesSize
};

#include <EngineModuleOpenGL46/ObjectView.h>
#include <EngineModuleOpenGL46/SystemComponent.h>
#include <EngineModuleOpenGL46/Shader/Shader.h>

#include <EngineModuleOpenGL46/Model/RenderQuad.h>


#include <EngineUtilities/View/camera.h>//clean up and make a base class shared by every class that needs cameras, CameraSystem

class BaseSubsystem : public RenderInterface
{
public:
	static Camera* m_camera;

protected:
	RenderQuad* m_quad;

	SubsystemState m_subsystemState;

	std::map<int, std::function<void()>> m_OnEnterForState;
	std::map<int, std::function<void()>> m_OnExitForState;
	std::map<int, std::function<void()>> m_DrawForState;

	vector<ObjectView*>* m_objectViews;
	
	std::vector<SystemComponentType> m_recipe;//turn into a map of strings to avoid enum here
	std::vector<SystemComponent*> m_components;

	std::vector <Shader*> m_shaders;
	std::vector<ShaderNames> m_shaderRecipe;//turn into a map of strings to avoid enum here

	unsigned int m_currentState;
	unsigned int m_stateCount;

public:
	BaseSubsystem();
	virtual bool Init(const std::map<SystemComponentType, SystemComponent*>& map, const std::map< ShaderNames, Shader* >& shadermap) = 0;
	void Update(float deltaTime);//todo remove if not needed
	std::vector<SystemComponentType>* GetRecipe();
	std::vector<ShaderNames>* GetShaderRecipe();

	SystemComponent* GetComponent(SystemComponentType name);
	Shader* GetComponent(ShaderNames name);

	static void SetCamera(Camera * camera);

	void QueryStepProgress(unsigned int * state) const;
	void QueryStepCount(unsigned int* stateCount) const;

	virtual void Deactivate() = 0;
	virtual void Activate() = 0;

	virtual bool CanAdvance() = 0;
	virtual void Advance() = 0;
	virtual void Draw( vector<ObjectView*> * objectViews ) = 0;

protected:
	virtual void OnEnterActive() = 0;
	virtual void ActiveBehavior() = 0;//todo remove if not needed
	virtual void OnExitActive() = 0;

	virtual void OnEnterInactive() = 0;
	virtual void InactiveBehavior() = 0;//todo remove if not needed
	virtual void OnExitInactive() = 0;

	void SubsystemOnEnterForState(const int state);
	void SubsystemOnExitForState(const int state);
	void SubsystemDrawForState(const int state);
public:
	void SubSystemExitCurrentState();

};

#endif