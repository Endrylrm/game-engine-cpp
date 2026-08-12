#include "engine/ecs/systems/MovementSystem.hpp"

#include <engine/ecs/components/Transform.hpp>
#include <engine/ecs/components/Velocity.hpp>

void MovementSystem::onUpdate(float deltaTime)
{
    for (auto [transform, velocity] : registry.view<Transform, Velocity>())
    {
        transform.position += velocity.linear * deltaTime;
    }
}
