#pragma once
#include "engine/entities/components/Component.hpp"
#include "engine/core/math/Rect2D.hpp"

class Collider : public Component
{
    virtual Rect2D GetAABB() const = 0;
};
