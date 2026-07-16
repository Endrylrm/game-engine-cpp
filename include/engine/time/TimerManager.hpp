#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "engine/time/Timer.hpp"

class TimerManager
{
public:
    Timer *createTimer(float waitTime, bool oneShot = false, bool autostart = false);
    Timer *after(float seconds, Timer::TimeoutCallback callback);
    void onUpdate(float deltaTime);
    void clear();
    size_t activeCount() const;

private:
    std::vector<std::unique_ptr<Timer>> timers;
};
