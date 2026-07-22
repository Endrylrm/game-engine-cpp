#pragma once
#include <cstdint>

enum class LifetimeState : uint8_t
{
    PendingSpawn,
    PendingAwake,
    PendingStart,
    Alive,
    PendingDestruction
};
