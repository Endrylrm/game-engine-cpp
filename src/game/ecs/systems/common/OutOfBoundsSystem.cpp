#include "game/ecs/systems/common/OutOfBoundsSystem.hpp"

#include <engine/api/WindowAPI.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/ecs/components/Transform.hpp>

#include <game/ecs/components/common/OutOfBounds.hpp>

void OutOfBoundsSystem::onUpdate(World &world, float deltaTime)
{
    for (auto [entity, transform, outOfBounds] :
         world.view<Transform, OutOfBounds>().withEntities())
    {
        if (isOutOfBounds(transform.position, outOfBounds.margin))
        {
            world.destroyEntity(entity);
            LOG_DEBUG(
                "Queued destruction for Entity ID: {}, generation: {}", entity.id, entity.generation
            );
        }
    }
}

bool OutOfBoundsSystem::isOutOfBounds(Vector2D position, float margin)
{
    if (position.y < -margin)
    {
        return true;
    }
    if (position.y > WindowAPI::getHeight() + margin)
    {
        return true;
    }
    if (position.x < -margin)
    {
        return true;
    }
    if (position.x > WindowAPI::getWidth() + margin)
    {
        return true;
    }
    return false;
}
