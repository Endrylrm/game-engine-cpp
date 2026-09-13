#pragma once
#include <engine/ecs/systems/System.hpp>
#include <engine/ecs/world/World.hpp>

class DeathSystem final : public System
{
public:
    void onPostUpdate(World &world) override;
};
