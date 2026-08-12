#pragma once
#include <engine/core/math/Vector2D.hpp>

struct BoxCollider
{
    Vector2D size{};
    Vector2D offset{};
    bool trigger{false};
};
