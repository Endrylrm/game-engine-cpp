#pragma once
#include <functional>

class Timer
{
public:
    using TimeoutCallback = std::function<void()>;

    Timer() = default;
    explicit Timer(float waitTime, bool oneShot = false, bool autostart = false)
        : waitTime(waitTime), oneShot(oneShot), autostart(autostart)
    {
        if (autostart)
            start();
    }

    void start(float newWaitTime = -1.0f);
    void stop();
    void pause();
    void resume();
    void onUpdate(float deltaTime);

    void setWaitTime(float time);
    void setOneShot(bool value);
    void setOnTimeout(TimeoutCallback callback);

    float getTimeLeft() const;
    float getWaitTime() const;

    bool isRunning() const;
    bool isPaused() const;
    bool isOneShot() const;

private:
    float waitTime = 1.0f;
    float timeLeft = 0.0f;
    bool oneShot = false;
    bool autostart = false;
    bool running = false;
    bool paused = false;

    TimeoutCallback onTimeout;
};
