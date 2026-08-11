#pragma once
#include <cstdint>

struct EntitySlot
{
    uint32_t generation = 0;
    bool alive = false;
};