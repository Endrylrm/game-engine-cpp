#include "engine/ecs/systems/LifetimeSystem.hpp"

#include <engine/ecs/components/Lifetime.hpp>

void LifetimeSystem::onUpdate(float deltaTime)
{
    for (auto [entity, lifetime] : registry.view<Lifetime>().withEntities())
    {
        lifetime.remaining -= deltaTime;

        if (lifetime.remaining <= 0.0f)
            registry.destroyEntity(entity);
    }
}
