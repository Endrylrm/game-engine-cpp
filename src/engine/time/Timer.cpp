#include "engine/time/Timer.hpp"

void Timer::start(float new_wait_time /* = -1.0f */)
{
    if (new_wait_time >= 0.0f)
        wait_time = new_wait_time;

    time_left = wait_time;
    running = true;
    paused = false;
}

void Timer::stop()
{
    running = false;
    time_left = 0.0f;
}

void Timer::pause()
{
    paused = true;
}

void Timer::resume()
{
    paused = false;
}

void Timer::on_update(float delta_time)
{
    if (!running || paused)
        return;

    time_left -= delta_time;
    if (time_left <= 0.0f)
    {
        if (on_timeout)
            on_timeout();

        if (one_shot)
        {
            stop();
        }
        else
        {
            time_left += wait_time;
        }
    }
}

void Timer::set_wait_time(float time)
{
    wait_time = time;
}

void Timer::set_one_shot(bool value)
{
    one_shot = value;
}

void Timer::set_on_timeout(TimeoutCallback callback)
{
    on_timeout = std::move(callback);
}

float Timer::get_time_left() const
{
    return time_left;
}

float Timer::get_wait_time() const
{
    return wait_time;
}

bool Timer::is_running() const
{
    return running;
}

bool Timer::is_paused() const
{
    return paused;
}

bool Timer::is_one_shot() const
{
    return one_shot;
}
