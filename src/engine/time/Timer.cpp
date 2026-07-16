#include "engine/time/Timer.hpp"

void Timer::start(float newWaitTime /* = -1.0f */)
{
    if (newWaitTime >= 0.0f)
        waitTime = newWaitTime;
    timeLeft = waitTime;
    running = true;
    paused = false;
}

void Timer::stop()
{
    running = false;
    timeLeft = 0.0f;
}

void Timer::pause() { paused = true; }
void Timer::resume() { paused = false; }

void Timer::onUpdate(float deltaTime)
{
    if (!running || paused)
        return;

    timeLeft -= deltaTime;
    if (timeLeft <= 0.0f)
    {
        if (onTimeout)
            onTimeout();

        if (oneShot)
        {
            stop();
        }
        else
        {
            timeLeft += waitTime;
        }
    }
}

void Timer::setWaitTime(float time) { waitTime = time; }
void Timer::setOneShot(bool value) { oneShot = value; }
void Timer::setOnTimeout(TimeoutCallback callback) { onTimeout = std::move(callback); }

float Timer::getTimeLeft() const { return timeLeft; }
float Timer::getWaitTime() const { return waitTime; }
bool Timer::isRunning() const { return running; }
bool Timer::isPaused() const { return paused; }
bool Timer::isOneShot() const { return oneShot; }