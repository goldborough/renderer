#if !defined(SIMULATIONMODEL_H)
#define SIMULATIONMODEL_H

struct SimulationModel
{
	float m_frameNumber;


	SimulationModel();

	void Update(float frameNumber);

};

#endif