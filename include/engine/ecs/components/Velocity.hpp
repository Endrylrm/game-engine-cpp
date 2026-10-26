#pragma once
#include "engine/core/math/Vector2D.hpp"

struct Velocity
{
    Velocity() = default;
    Velocity(Vector2D linear) : linear(linear) {}
    Velocity(float linear_x, float linear_y) : linear{linear_x, linear_y} {}

    Vector2D linear{};
};
