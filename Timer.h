#pragma once
#include <chrono>

namespace chrono = std::chrono;

class Timer {
public:

	Timer();
	~Timer();

	float getElapsedTime();

private:

	chrono::system_clock clock;
	chrono::time_point<chrono::system_clock, chrono::duration<float, std::ratio<1, 1000>>> TP;
	float instTime;

};

