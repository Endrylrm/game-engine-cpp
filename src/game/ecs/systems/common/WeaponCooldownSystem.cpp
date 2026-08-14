#include "game/ecs/systems/common/WeaponCooldownSystem.hpp"

#include <game/ecs/components/common/Weapon.hpp>

void WeaponCooldownSystem::onUpdate(World &world, float deltaTime)
{
    for (auto [weapon] : world.view<Weapon>())
    {
        weapon.cooldownTimer -= deltaTime;

        if (weapon.cooldownTimer < 0.0f)
            weapon.cooldownTimer = 0.0f;
    }
}
