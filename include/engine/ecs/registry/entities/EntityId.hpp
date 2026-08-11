#pragma once
#include <cstdint>

struct EntityId
{
    uint32_t id;
    uint32_t generation;
};

constexpr bool operator==(const EntityId &a, const EntityId &b)
{
    return a.id == b.id && a.generation == b.generation;
}
