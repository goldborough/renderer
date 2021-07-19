#include "Simulation.h"

Simulation::Simulation()
{
	m_config = nullptr;
	m_view = nullptr;
	m_model = nullptr;
}

Simulation::~Simulation()
{
}

bool Simulation::Init(SimulationConfig* config, SimulationView* view, SimulationModel* model)
{
	m_config = config;
	m_view = view;
	m_model = model;

	if (!m_view->Init()) return false;
	
	return true;
}

void Simulation::Update(float frameNumber)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));

}

void Simulation::Render()
{
	m_view->Render();
}

void Simulation::Shutdown()
{
}

void Simulation::GetView()
{
}

void Simulation::GetModel()
{
}

void Simulation::GetConfig()
{
}
