#pragma once
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/systems/System.hpp>

class PlayerShootSystem : public System
{
public:
    explicit PlayerShootSystem(Registry &registry) : registry(registry) {}
    void onUpdate(float deltaTime) override;

private:
    void shoot(float x, float y);
    Registry &registry;
};
