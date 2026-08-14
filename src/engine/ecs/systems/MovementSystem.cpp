#include "engine/ecs/systems/MovementSystem.hpp"

#include <engine/ecs/components/Transform.hpp>
#include <engine/ecs/components/Velocity.hpp>

void MovementSystem::onUpdate(World &world, float deltaTime)
{
    for (auto [transform, velocity] : world.view<Transform, Velocity>())
    {
        transform.position += velocity.linear * deltaTime;
    }
}
