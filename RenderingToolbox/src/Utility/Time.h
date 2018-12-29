#pragma once
#include <chrono>

class Time {
public:
	friend class Application;

	Time();
	static float GetDeltaTime();

private:

	void Update();
};