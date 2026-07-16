#include "engine/time/Time.hpp"

std::chrono::duration<float> Time::getTargetFrameTime() const
{
    return targetFrameTime;
}

void Time::setTargetFPS(const uint32_t FPS)
{
    currentFPS = FPS;
    targetFrameTime = std::chrono::duration<float>(1.0 / currentFPS);
}

void Time::tick()
{
    auto now = Clock::now();
    deltaTime = std::chrono::duration<float>(now - lastTime).count();
    lastTime = now;
    deltaTime = std::min(deltaTime, 0.25f);
    accumulator += deltaTime;
}

int Time::consumeFixedSteps()
{
    int steps = 0;

    while (accumulator >= fixedDeltaTime)
    {
        accumulator -= fixedDeltaTime;
        ++steps;
    }

    return steps;
}

float Time::getDeltaTime() const
{
    return deltaTime;
}

float Time::getFixedDeltaTime() const
{
    return fixedDeltaTime;
}

uint32_t Time::getFPS() const
{
    return currentFPS;
}
