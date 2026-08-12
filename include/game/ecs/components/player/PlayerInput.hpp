#pragma once
#include <engine/core/math/Vector2D.hpp>

struct PlayerInput
{
    Vector2D move{};
    bool shoot{false};
};
