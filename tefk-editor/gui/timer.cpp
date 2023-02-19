#include "timer.hpp"

namespace tefk {

Timer::Timer()
	: _duration{ 0 }
	, _set{ false }
{}

void Timer::StartTimer(double milliseconds) {
	_startTime = std::chrono::system_clock::now();
	_duration = milliseconds;
	_set = true;
}

void Timer::StopTimer() {
	_set = false;
}

bool Timer::Ringing() {
	if (!_set)
		return false;

	auto now = std::chrono::system_clock::now();
	std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTime);
	return diff.count() >= _duration;
}

} // namespace tefk