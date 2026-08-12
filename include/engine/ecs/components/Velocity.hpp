#pragma once
#include <engine/core/math/Vector2D.hpp>

struct Velocity
{
    Velocity() = default;
    Velocity(Vector2D linear) : linear(linear) {}
    Velocity(float linearX, float linearY) : linear{linearX, linearY} {}

    Vector2D linear{};
};
