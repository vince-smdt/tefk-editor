#pragma once
#include <chrono>

namespace tefk {

class Timer {
	std::chrono::time_point<std::chrono::system_clock> _startTime;
	double _duration;
	bool _set;
public:
	Timer();
	void StartTimer(double milliseconds);
	void StopTimer();
	bool Ringing();
};

} // namespace tefk