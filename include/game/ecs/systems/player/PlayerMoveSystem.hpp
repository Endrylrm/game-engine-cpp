#pragma once
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/systems/System.hpp>

class PlayerMoveSystem : public System
{
public:
    explicit PlayerMoveSystem(Registry &registry) : registry(registry) {}
    void onUpdate(float deltaTime) override;

private:
    Registry &registry;
};
