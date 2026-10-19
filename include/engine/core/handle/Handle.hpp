#pragma once
#include <cstdint>
#include <functional>

struct Handle
{
    uint32_t index = UINT32_MAX;
    uint32_t generation = 0;

    bool isValid() const
    {
        return index != UINT32_MAX;
    }

    bool operator==(const Handle &other) const
    {
        return index == other.index && generation == other.generation;
    }

    bool operator!=(const Handle &other) const
    {
        return !(*this == other);
    }
};

template <>
struct std::hash<Handle>
{
    size_t operator()(const Handle &handle) const noexcept
    {
        return std::hash<uint32_t>{}(handle.index) ^
               (std::hash<uint32_t>{}(handle.generation) << 1);
    }
};
