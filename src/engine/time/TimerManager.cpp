#include "engine/time/TimerManager.hpp"

Timer *TimerManager::
    create_timer(float wait_time, bool one_shot /* = false */, bool autostart /* = false */)
{
    auto timer = std::make_unique<Timer>(wait_time, one_shot, autostart);
    Timer *raw = timer.get();
    timers.push_back(std::move(timer));
    return raw;
}

Timer *TimerManager::after(float seconds, Timer::TimeoutCallback callback)
{
    Timer *timer = create_timer(seconds, true, true);
    timer->set_on_timeout(std::move(callback));
    return timer;
}

void TimerManager::on_update(float delta_time)
{
    for (auto &timer : timers)
    {
        timer->on_update(delta_time);
    }

    std::erase_if(
        timers,
        [](const std::unique_ptr<Timer> &timer)
        { return timer->is_one_shot() && !timer->is_running(); }
    );
}

void TimerManager::clear()
{
    timers.clear();
}

size_t TimerManager::active_count() const
{
    return timers.size();
}
