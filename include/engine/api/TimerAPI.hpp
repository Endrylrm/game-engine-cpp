#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/time/TimerManager.hpp"
#include "engine/time/Timer.hpp"

class TimerAPI : public ManagerAPI<TimerManager>
{
public:
    static Timer *createTimer(float waitTime, bool oneShot = false, bool autostart = false)
    {
        return getManager().createTimer(waitTime, oneShot, autostart);
    }

    static Timer *after(float seconds, Timer::TimeoutCallback callback)
    {
        return getManager().after(seconds, std::move(callback));
    }
};