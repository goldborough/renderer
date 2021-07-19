#if !defined(SIMULATION_H)
#define SIMULATION_H

#include <string>
using std::string;

#include "../SimulationView/SimulationView.h"
#include "../SimulationModel/SimulationModel.h"

struct SimulationConfig
{
	unsigned long m_id;
	string m_name;
	float m_totalTime;
};

class Simulation
{
protected:
	SimulationConfig * m_config;
	SimulationView * m_view;
	SimulationModel * m_model;

public:
	Simulation();
	~Simulation();

	bool Init(SimulationConfig* config, SimulationView* view, SimulationModel* model);

	void Update(float frameNumber);
	void Render();

	void Shutdown();

	void GetView();
	void GetModel();
	void GetConfig();
};

#endif