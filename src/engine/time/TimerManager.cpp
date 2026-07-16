#include "engine/time/TimerManager.hpp"

Timer *TimerManager::createTimer(float waitTime, bool oneShot /* = false */, bool autostart /* = false */)
{
    auto timer = std::make_unique<Timer>(waitTime, oneShot, autostart);
    Timer *raw = timer.get();
    timers.push_back(std::move(timer));
    return raw;
}

Timer *TimerManager::after(float seconds, Timer::TimeoutCallback callback)
{
    Timer *timer = createTimer(seconds, true, true);
    timer->setOnTimeout(std::move(callback));
    return timer;
}

void TimerManager::onUpdate(float deltaTime)
{
    for (auto &timer : timers)
    {
        timer->onUpdate(deltaTime);
    }

    std::erase_if(timers, [](const std::unique_ptr<Timer> &timer)
                  { return timer->isOneShot() && !timer->isRunning(); });
}

void TimerManager::clear()
{
    timers.clear();
}

size_t TimerManager::activeCount() const { return timers.size(); }