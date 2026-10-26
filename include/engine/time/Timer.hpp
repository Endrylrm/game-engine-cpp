#pragma once
#include <functional>

class Timer
{
public:
    using TimeoutCallback = std::function<void()>;

    Timer() = default;
    explicit Timer(float wait_time, bool one_shot = false, bool autostart = false)
        : wait_time(wait_time), one_shot(one_shot), autostart(autostart)
    {
        if (autostart)
            start();
    }

    void start(float new_wait_time = -1.0f);
    void stop();
    void pause();
    void resume();
    void on_update(float delta_time);

    void set_wait_time(float time);
    void set_one_shot(bool value);
    void set_on_timeout(TimeoutCallback callback);

    float get_time_left() const;
    float get_wait_time() const;

    bool is_running() const;
    bool is_paused() const;
    bool is_one_shot() const;

private:
    float wait_time{1.0f};
    float time_left{0.0f};
    bool one_shot{false};
    bool autostart{false};
    bool running{false};
    bool paused{false};

    TimeoutCallback on_timeout;
};
