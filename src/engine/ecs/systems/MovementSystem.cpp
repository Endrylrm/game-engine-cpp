#include "engine/ecs/systems/MovementSystem.hpp"

#include "engine/ecs/components/Transform.hpp"
#include "engine/ecs/components/Velocity.hpp"

void MovementSystem::on_update(World &world, float delta_time)
{
    for (auto [transform, velocity] : world.view<Transform, Velocity>())
    {
        transform.position += velocity.linear * delta_time;
    }
}
