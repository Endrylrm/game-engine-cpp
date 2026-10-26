#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/time/Timer.hpp"
#include "engine/time/TimerManager.hpp"

class TimerAPI : public ManagerAPI<TimerManager>
{
public:
    static Timer *create_timer(float wait_time, bool one_shot = false, bool autostart = false)
    {
        return get_manager().create_timer(wait_time, one_shot, autostart);
    }

    static Timer *after(float seconds, Timer::TimeoutCallback callback)
    {
        return get_manager().after(seconds, std::move(callback));
    }
};
