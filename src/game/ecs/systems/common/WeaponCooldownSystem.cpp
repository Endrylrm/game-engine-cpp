#include "game/ecs/systems/common/WeaponCooldownSystem.hpp"

#include "game/ecs/components/common/Weapon.hpp"

void WeaponCooldownSystem::on_update(World &world, float delta_time)
{
    for (auto [weapon] : world.view<Weapon>())
    {
        weapon.cooldown_timer -= delta_time;

        if (weapon.cooldown_timer < 0.0f)
            weapon.cooldown_timer = 0.0f;
    }
}
