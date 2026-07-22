#pragma once
#include <cstdint>

enum class EntityStateFlags : uint8_t
{
    None = 0,
    Active = 1 << 0,
    Deactivated = 1 << 1,
    Visible = 1 << 2,
    Static = 1 << 3,
};

inline EntityStateFlags operator|(EntityStateFlags a, EntityStateFlags b)
{
    return static_cast<EntityStateFlags>(
        static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline EntityStateFlags operator&(EntityStateFlags a, EntityStateFlags b)
{
    return static_cast<EntityStateFlags>(
        static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline EntityStateFlags operator~(EntityStateFlags a)
{
    return static_cast<EntityStateFlags>(
        ~static_cast<uint8_t>(a));
}

inline EntityStateFlags &operator|=(EntityStateFlags &a, EntityStateFlags b)
{
    return a = a | b;
}

inline EntityStateFlags &operator&=(EntityStateFlags &a, EntityStateFlags b)
{
    return a = a & b;
}