#pragma once
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/systems/System.hpp>

class WeaponCooldownSystem : public System
{
public:
    explicit WeaponCooldownSystem(Registry &registry) : registry(registry) {}
    void onUpdate(float deltaTime) override;

private:
    Registry &registry;
};