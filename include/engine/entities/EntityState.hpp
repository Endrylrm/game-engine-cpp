#pragma once
#include <cstdint>

enum class EntityState : uint8_t
{
    None = 0,
    PendingSpawn = 1 << 0,
    PendingAwake = 1 << 1,
    PendingStart = 1 << 2,
    Active = 1 << 3,
    Deactivated = 1 << 4,
    Visible = 1 << 5,
    PendingDestruction = 1 << 6
};

inline EntityState operator|(EntityState a, EntityState b)
{
    return static_cast<EntityState>(
        static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline EntityState operator&(EntityState a, EntityState b)
{
    return static_cast<EntityState>(
        static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline EntityState operator~(EntityState a)
{
    return static_cast<EntityState>(
        ~static_cast<uint8_t>(a));
}

inline EntityState &operator|=(EntityState &a, EntityState b)
{
    return a = a | b;
}

inline EntityState &operator&=(EntityState &a, EntityState b)
{
    return a = a & b;
}