#include "game/ecs/systems/common/DamageSystem.hpp"

#include "engine/core/log/Log.hpp"

#include "game/ecs/components/common/Damage.hpp"
#include "game/ecs/components/common/Dead.hpp"
#include "game/ecs/components/common/Health.hpp"

void DamageSystem::on_post_update(World &world)
{
    for (auto [entity, health, damage] : world.view<Health, Damage>().with_entities())
    {
        health.current -= damage.amount;
        LOG_DEBUG("Damaged Entity by {} damage", damage.amount);
        LOG_DEBUG("Current Health is {}", health.current);

        if (health.current <= 0 && world.is_valid_entity(entity))
        {
            world.add_component<Dead>(entity);
        }

        world.remove_component<Damage>(entity);
    }
}
