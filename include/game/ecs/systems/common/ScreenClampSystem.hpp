#pragma once
#include <engine/ecs/systems/System.hpp>
#include <engine/ecs/world/World.hpp>

class ScreenClampSystem : public System
{
public:
    void onPostUpdate(World &world) override;
};
