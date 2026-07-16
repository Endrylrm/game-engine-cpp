#pragma once

class Audio
{
public:
    virtual ~Audio() = default;
    virtual void PlayAudio() = 0;
    virtual void StopAudio() = 0;
};