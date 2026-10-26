#pragma once
#include "engine/ecs/systems/System.hpp"
#include "engine/ecs/world/World.hpp"

class ScreenClampSystem final : public System
{
public:
    void on_post_update(World &world) override;
};
