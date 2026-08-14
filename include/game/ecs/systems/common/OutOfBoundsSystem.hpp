#pragma once
#include <engine/core/math/Vector2D.hpp>
#include <engine/ecs/systems/System.hpp>
#include <engine/ecs/world/World.hpp>

class OutOfBoundsSystem : public System
{
public:
    void onUpdate(World &world, float deltaTime) override;

private:
    bool isOutOfBounds(Vector2D position, float margin);
};
