#include "Time.h"
#include "FunctionTimer.h"

namespace Rb {

	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> lastFrame;

	float deltaTime = 0;

	Time::Time()
	{

	}

	float Time::GetDeltaTime()
	{
		return deltaTime;
	}

	void Time::Init()
	{	
		start = std::chrono::high_resolution_clock::now();
		lastFrame = start;
	}

	void Time::Update()
	{

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> sec = (now - lastFrame);
		deltaTime = sec.count();

		lastFrame = now;
	}

}

