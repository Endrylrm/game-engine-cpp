#pragma once
#include <engine/ecs/systems/System.hpp>
#include <engine/ecs/world/World.hpp>

class DamageSystem : public System
{
public:
    void onPostUpdate(World &world) override;
};
