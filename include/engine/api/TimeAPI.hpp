#pragma once
#include <cstdint>

#include "engine/api/ManagerAPI.hpp"
#include "engine/time/Time.hpp"

class TimeAPI : public ManagerAPI<Time>
{
public:
    static float get_delta_time()
    {
        return get_manager().get_delta_time();
    }

    static float get_fixed_delta_time()
    {
        return get_manager().get_fixed_delta_time();
    }

    static uint32_t get_fps()
    {
        return get_manager().get_fps();
    }
};
