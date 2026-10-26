#pragma once
#include "engine/ecs/systems/System.hpp"
#include "engine/ecs/world/World.hpp"

class PlayerInputSystem final : public System
{
public:
    void on_update(World &world, float delta_time) override;
};
