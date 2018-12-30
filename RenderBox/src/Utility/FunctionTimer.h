#pragma once
#include <chrono>
#include <iostream>

struct RB_API FunctionTimer {

	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration <float> duration;

	FunctionTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~FunctionTimer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "Function took" << ms << std::endl;
	}
};
