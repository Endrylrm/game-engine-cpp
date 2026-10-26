#pragma once
#include "engine/ecs/world/World.hpp"

#include "System.hpp"

class MovementSystem final : public System
{
public:
    void on_update(World &world, float delta_time) override;
};
