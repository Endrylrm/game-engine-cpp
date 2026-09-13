#pragma once
#include <engine/ecs/world/World.hpp>

#include "System.hpp"

class MovementSystem final : public System
{
public:
    void onUpdate(World &world, float deltaTime) override;
};
