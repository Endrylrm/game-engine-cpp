#pragma once
#include "engine/core/math/Vector2D.hpp"
#include "engine/ecs/systems/System.hpp"
#include "engine/ecs/world/World.hpp"

class OutOfBoundsSystem final : public System
{
public:
    void on_update(World &world, float delta_time) override;

private:
    bool is_out_of_bounds(Vector2D position, float margin);
};
