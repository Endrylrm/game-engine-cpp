#include "engine/time/Time.hpp"

std::chrono::duration<float> Time::get_target_frame_time() const
{
    return target_frame_time;
}

void Time::set_target_fps(const uint32_t fps)
{
    current_fps = fps;
    target_frame_time = std::chrono::duration<float>(1.0 / current_fps);
}

void Time::tick()
{
    auto now = Clock::now();
    delta_time = std::chrono::duration<float>(now - last_time).count();
    last_time = now;
    delta_time = std::min(delta_time, 0.25f);
    accumulator += delta_time;
}

int Time::consume_fixed_steps()
{
    int steps = 0;

    while (accumulator >= fixed_delta_time)
    {
        accumulator -= fixed_delta_time;
        ++steps;
    }

    return steps;
}

float Time::get_delta_time() const
{
    return delta_time;
}

float Time::get_fixed_delta_time() const
{
    return fixed_delta_time;
}

uint32_t Time::get_fps() const
{
    return current_fps;
}
