#if !defined(SIMULATIONVIEWFACTORY_H)
#define SIMULATIONVIEWFACTORY_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <EngineModuleOpenGL46/ObjectView.h>


#include "../SimulationView/SimulationView.h"
#include "../Control/Simulation.h"

class SimulationViewFactory
{
private:
	vector<ObjectView*> m_objectViews;


public:
	SimulationViewFactory();
	~SimulationViewFactory();

	SimulationView * GetView(SimulationConfig * config);

	ObjectView* RetrieveModel(string path);
	ObjectView* RetrievePrimitive(string type);


};
#endif


