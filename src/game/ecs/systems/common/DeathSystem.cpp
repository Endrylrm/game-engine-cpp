#include "game/ecs/systems/common/DeathSystem.hpp"

#include "engine/core/log/Log.hpp"

#include "game/ecs/components/common/Dead.hpp"

void DeathSystem::on_post_update(World &world)
{
    for (auto [entity, _] : world.view<Dead>().with_entities())
    {
        world.destroy_entity(entity);
        LOG_DEBUG(
            "Queued destruction for Entity ID: {}, generation: {}", entity.index, entity.generation
        );
    }
}
