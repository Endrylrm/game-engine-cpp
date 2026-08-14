#include "engine/ecs/systems/LifetimeSystem.hpp"

#include <engine/ecs/components/Lifetime.hpp>

void LifetimeSystem::onUpdate(World &world, float deltaTime)
{
    for (auto [entity, lifetime] : world.view<Lifetime>().withEntities())
    {
        lifetime.remaining -= deltaTime;

        if (lifetime.remaining <= 0.0f)
            world.destroyEntity(entity);
    }
}
