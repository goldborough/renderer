#include "SimulationController.h"

OpenGLObject * SimulationController::m_renderObject = nullptr;

SimulationController::SimulationController()
{
	m_simulation = nullptr;
	m_finished = false;
}

SimulationController::~SimulationController()
{
}

bool SimulationController::Run(SimulationConfig* config)
{

	m_simulation = new Simulation();
	m_renderObject = new OpenGLObject();

	if (!m_renderObject->Init()) return false;
	
	SimulationView::openGLObject = m_renderObject;
	
	m_renderObject->BeginScene();
	m_renderObject->EndScene();

	SimulationView * view = m_factory.GetView(config);
	SimulationModel * model = nullptr;

	//eventually while (loading)
	if (!m_simulation->Init(config, view, model)) return false;
	
	m_finished = false;
	m_timeElapsed = 0.0f;
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_lastCount);
	
	while (!m_finished)
	{
		if (!ProcessMessages())
		{
			QueryPerformanceCounter(&m_CurrentCount);
			
			m_simulation->Update(TimeElapsed());
			m_simulation->Render();
			
			Yield();
			m_lastCount = m_CurrentCount;
		}

		if (PlatformShouldIClose()) return false;
	}

	return true;
}

void SimulationController::Shutdown()
{
	delete m_simulation;
}

bool SimulationController::ProcessMessages()
{
	/*
	if (PeekMessage(&m_msg, NULL, NULL, NULL, PM_REMOVE))
	{
		if (m_msg.message == WM_QUIT)
		{
			m_finished = true; OutputDebugString(L"QUIT");
		}

		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
		return true;
	}*/

	return false;
}