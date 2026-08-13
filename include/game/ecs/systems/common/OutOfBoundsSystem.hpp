#pragma once
#include <engine/core/math/Vector2D.hpp>
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/systems/System.hpp>

class OutOfBoundsSystem : public System
{
public:
    explicit OutOfBoundsSystem(Registry &registry) : registry(registry) {}
    void onUpdate(float deltaTime) override;

private:
    bool isOutOfBounds(Vector2D position, float margin);
    Registry &registry;
};
