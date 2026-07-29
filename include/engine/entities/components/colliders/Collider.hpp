#pragma once
#include "engine/core/math/Rect2D.hpp"
#include "engine/entities/components/Component.hpp"

class Collider : public Component
{
    virtual Rect2D GetAABB() const = 0;
};
