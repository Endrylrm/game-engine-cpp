#pragma once
#include <cstdint>
#include "engine/api/ManagerAPI.hpp"
#include "engine/time/Time.hpp"

class TimeAPI : public ManagerAPI<Time>
{
public:
    float getDeltaTime() const
    {
        return getManager().getDeltaTime();
    }

    float getFixedDeltaTime() const
    {
        return getManager().getFixedDeltaTime();
    }

    uint32_t getFPS() const
    {
        return getManager().getFPS();
    }
};