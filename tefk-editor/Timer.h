#pragma once
#include <chrono>

namespace tefk {

class Timer
{
public:
    Timer();
    void StartTimer(double milliseconds);
    void StopTimer();
    bool Ringing();
private:
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    double _duration;
    bool _set;
};

} // namespace tefk
