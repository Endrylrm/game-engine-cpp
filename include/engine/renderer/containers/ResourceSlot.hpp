#pragma once
#include <cstdint>
#include <optional>

template <typename NativeResource>
struct ResourceSlot
{
    std::optional<NativeResource> resource;
    uint32_t generation = 0;
    bool alive = false;
};
