#include "TimestepController.h"

TimestepController::TimestepController()
{
	m_timeElapsed = 0.0f;
}

TimestepController::~TimestepController()
{
}

float TimestepController::TimeElapsed()
{
	m_timeElapsed = (m_CurrentCount.QuadPart - m_lastCount.QuadPart) / (float)m_frequency.QuadPart;

	return m_timeElapsed;
}
