#pragma once
#include <engine/ecs/registry/Registry.hpp>

#include "System.hpp"

class MovementSystem : public System
{
public:
    explicit MovementSystem(Registry &registry) : registry(registry) {}
    void onUpdate(float deltaTime) override;

private:
    Registry &registry;
};
