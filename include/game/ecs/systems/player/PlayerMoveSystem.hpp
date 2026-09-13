#pragma once
#include <engine/ecs/systems/System.hpp>
#include <engine/ecs/world/World.hpp>

class PlayerMoveSystem final : public System
{
public:
    void onUpdate(World &world, float deltaTime) override;
};
