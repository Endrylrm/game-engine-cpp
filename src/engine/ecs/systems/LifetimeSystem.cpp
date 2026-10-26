#include "engine/ecs/systems/LifetimeSystem.hpp"

#include "engine/ecs/components/Lifetime.hpp"

void LifetimeSystem::on_update(World &world, float delta_time)
{
    for (auto [entity, lifetime] : world.view<Lifetime>().with_entities())
    {
        lifetime.remaining -= delta_time;

        if (lifetime.remaining <= 0.0f)
            world.destroy_entity(entity);
    }
}
