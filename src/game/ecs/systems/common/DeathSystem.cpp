#include "game/ecs/systems/common/DeathSystem.hpp"

#include <engine/core/log/Log.hpp>

#include <game/ecs/components/common/Dead.hpp>

void DeathSystem::onUpdate(World &world, float deltaTime)
{
    for (auto [entity, d] : world.view<Dead>().withEntities())
    {
        world.destroyEntity(entity);
        LOG_DEBUG(
            "Queued destruction for Entity ID: {}, generation: {}", entity.id, entity.generation
        );
    }
}
