#pragma once
#include <engine/audio/Audio.hpp>

class SDLAudio : public Audio
{
public:
    ~SDLAudio() override = default;
    void PlayAudio() override {}
    void StopAudio() override {}
};