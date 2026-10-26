#pragma once
#include <memory>
#include <vector>

#include "Timer.hpp"

class TimerManager
{
public:
    Timer *create_timer(float wait_time, bool one_shot = false, bool autostart = false);
    Timer *after(float seconds, Timer::TimeoutCallback callback);
    void on_update(float delta_time);
    void clear();
    size_t active_count() const;

private:
    std::vector<std::unique_ptr<Timer>> timers{};
};
