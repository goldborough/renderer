#if !defined(SIMULATIONCONTROLLER_H)
#define SIMULATIONCONTROLLER_H

#include "TimestepController.h"
#include "Simulation.h"

#include "../ViewFactory/SimulationViewFactory.h"
#include <EngineModuleOpenGL46/OpenGLObject.h>

class SimulationController : public TimestepController
{
protected:
	Simulation * m_simulation;
	SimulationViewFactory m_factory;
	static OpenGLObject * m_renderObject;

	bool m_finished = false;
	MSG m_msg;

public:
	SimulationController();
	~SimulationController();
	bool Run(SimulationConfig * config);
	void Shutdown();


	bool ProcessMessages();
};


#endif