#pragma once
#include <cstdint>
#include "engine/api/ManagerAPI.hpp"
#include "engine/time/Time.hpp"

class TimeAPI : public ManagerAPI<Time>
{
public:
    static float getDeltaTime()
    {
        return getManager().getDeltaTime();
    }

    static float getFixedDeltaTime()
    {
        return getManager().getFixedDeltaTime();
    }

    static uint32_t getFPS()
    {
        return getManager().getFPS();
    }
};