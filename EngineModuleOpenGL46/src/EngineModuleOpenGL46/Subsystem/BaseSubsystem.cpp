#include "BaseSubsystem.h"

Camera * BaseSubsystem::m_camera = nullptr;

BaseSubsystem::BaseSubsystem()
{
	m_subsystemState = subsystemInactive;
	m_quad = nullptr;
}

void BaseSubsystem::Update(float deltaTime)
{
	switch (m_subsystemState)
	{
	case subsystemActive:
		ActiveBehavior();
	}
}

std::vector<SystemComponentType>* BaseSubsystem::GetRecipe()
{
	return &m_recipe;
}

std::vector<ShaderNames>* BaseSubsystem::GetShaderRecipe()
{
	return &m_shaderRecipe;
}

SystemComponent* BaseSubsystem::GetComponent(SystemComponentType name)
{
	return m_components.at(name);
}

Shader* BaseSubsystem::GetComponent(ShaderNames name)
{
	return m_shaders.at(name);
}

void BaseSubsystem::QueryStepProgress(unsigned int* state) const
{
	*state = m_currentState;
}

void BaseSubsystem::QueryStepCount(unsigned int* stateCount) const
{
	*stateCount = m_stateCount;
}

void BaseSubsystem::Activate()
{
	DebugPrint("BaseSubsystem::Activate()");
	if (m_subsystemState != subsystemActive)
	{
		OnEnterActive();
	}
}
void BaseSubsystem::SetCamera(Camera * camera)
{
	m_camera = camera;
}

void BaseSubsystem::SubsystemOnEnterForState(const int state)
{
	//std::pair < int, std::function<void()> > p = *m_OnEnterForState.find(state);
	//p.second();

	(*m_OnEnterForState.find(state)).second();
}

void BaseSubsystem::SubsystemOnExitForState(const int state)
{
	//std::pair < int, std::function<void()> > p = *m_OnExitForState.find(state);
	//p.second();

	(*m_OnExitForState.find(state)).second();

}

void BaseSubsystem::SubsystemDrawForState(const int state)
{
	DebugPrint("SubsystemDrawForState()");
	(*m_DrawForState.find(state)).second();
}

void BaseSubsystem::SubSystemExitCurrentState()
{
	(*m_OnExitForState.find(m_currentState)).second();
}