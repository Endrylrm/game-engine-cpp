#include "game/ecs/systems/common/DamageSystem.hpp"

#include <engine/core/log/Log.hpp>

#include <game/ecs/components/common/Damage.hpp>
#include <game/ecs/components/common/Dead.hpp>
#include <game/ecs/components/common/Health.hpp>

void DamageSystem::onPostUpdate(World &world)
{
    for (auto [entity, health, damage] : world.view<Health, Damage>().withEntities())
    {
        health.current -= damage.amount;
        LOG_DEBUG("Damaged Entity by {} damage", damage.amount);
        LOG_DEBUG("Current Health is {}", health.current);

        if (health.current <= 0 && world.isValidEntity(entity))
        {
            world.addComponent<Dead>(entity);
        }

        world.removeComponent<Damage>(entity);
    }
}
