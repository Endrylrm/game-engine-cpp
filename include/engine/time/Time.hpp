#pragma once
#include <chrono>
#include <cstdint>

class Time
{
public:
    std::chrono::duration<float> getTargetFrameTime() const;
    void setTargetFPS(const uint32_t FPS);

    void tick();

    int consumeFixedSteps();
    float getDeltaTime() const;
    float getFixedDeltaTime() const;
    uint32_t getFPS() const;

private:
    using Clock = std::chrono::steady_clock;
    Clock::time_point lastTime = Clock::now();

    float deltaTime = 0.0f;
    float fixedDeltaTime = 1.0f / 60.0f;
    float accumulator = 0.0f;
    float maxAccumulator = 0.25f;
    uint32_t currentFPS = 60;

    std::chrono::duration<float> targetFrameTime = std::chrono::duration<float>(1.0 / 60.0);
};
