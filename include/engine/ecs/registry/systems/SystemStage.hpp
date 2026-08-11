#pragma once
#include <cstdint>

enum class SystemStage : uint8_t
{
    None = 0,
    Physics = 1 << 0,
    PreUpdate = 1 << 1,
    Update = 1 << 2,
    PostUpdate = 1 << 3,
    Render = 1 << 4
};
