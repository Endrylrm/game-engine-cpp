#pragma once
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/systems/System.hpp>

class LifetimeSystem : public System
{
public:
    explicit LifetimeSystem(Registry &registry) : registry(registry) {}
    void onUpdate(float deltaTime) override;

private:
    Registry &registry;
};
