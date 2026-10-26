#pragma once
#include <chrono>
#include <cstdint>

class Time
{
public:
    std::chrono::duration<float> get_target_frame_time() const;
    void set_target_fps(const uint32_t fps);

    void tick();

    int consume_fixed_steps();
    float get_delta_time() const;
    float get_fixed_delta_time() const;
    uint32_t get_fps() const;

private:
    using Clock = std::chrono::steady_clock;
    Clock::time_point last_time = Clock::now();

    float delta_time{0.0f};
    float fixed_delta_time{1.0f / 60.0f};
    float accumulator{0.0f};
    float max_accumulator{0.25f};
    uint32_t current_fps{60};

    std::chrono::duration<float> target_frame_time{std::chrono::duration<float>(1.0 / 60.0)};
};
