#if !defined(TIMESTEPCONTROLLER_H)
#define TIMESTEPCONTROLLER_H


#include <vector>
using std::vector;



#include <windows.h>

#include <EngineModuleOpenGL46/Control/PlatformController.h>

struct FrameTimer
{
	vector<float> m_frameTimes;
	unsigned int m_vectorSize;
	unsigned int m_thisFrameIndex;
	unsigned int m_frameTimeAverage;

	FrameTimer()
	{
		m_vectorSize = 60;
		m_frameTimes.resize(m_vectorSize);
		m_thisFrameIndex = 0;
		m_frameTimeAverage = 0;
	};

	void Update(float deltaTime)
	{
		m_frameTimes.at(m_thisFrameIndex) = deltaTime;

		if (m_thisFrameIndex == m_vectorSize - 1) m_thisFrameIndex = 0;
		else m_thisFrameIndex++;
	}

	float AverageFrameTimeOneSecond()
	{
		float count = 0.0f;
		m_frameTimeAverage = 0.0f;
		int i;

		for (i = 0; i < m_frameTimes.size(); i++)
		{
			if ( (count + m_frameTimes.at(i)) * 1000.f > 1.0f)
			{
				break;
			}
			
			count += m_frameTimes.at(i);
		}

		if (i > 0)
		{
			m_frameTimeAverage = count * 1000.f / i;
		}
		m_frameTimeAverage = 0.0f;

		return 0.0f;
	}

	float GetAverageAsFPS()
	{
		if (m_frameTimeAverage > 0.0f) return 1.0f / m_frameTimeAverage;

		return 0.0f;
	}
};

class TimestepController : protected PlatformController
{
protected:
	LARGE_INTEGER m_frequency;
	LARGE_INTEGER m_lastCount;
	LARGE_INTEGER m_CurrentCount;
	double m_timeElapsed;

	FrameTimer m_frameTimer;
public:
	TimestepController();
	~TimestepController();

	float TimeElapsed();
};
#endif