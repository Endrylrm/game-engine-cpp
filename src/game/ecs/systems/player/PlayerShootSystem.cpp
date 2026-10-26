#include "game/ecs/systems/player/PlayerShootSystem.hpp"

#include "engine/api/AssetsAPI.hpp"
#include "engine/api/EntityAPI.hpp"
#include "engine/assets/AssetHandle.hpp"
#include "engine/core/log/Log.hpp"
#include "engine/ecs/components/Renderable.hpp"
#include "engine/ecs/components/Sprite.hpp"
#include "engine/ecs/components/Transform.hpp"
#include "engine/ecs/components/Velocity.hpp"
#include "engine/ecs/handle/Entity.hpp"
#include "engine/renderer/resources/Texture.hpp"

#include "game/ecs/components/common/OutOfBounds.hpp"
#include "game/ecs/components/common/Weapon.hpp"
#include "game/ecs/components/player/PlayerInput.hpp"

void PlayerShootSystem::on_update(World &world, float delta_time)
{
    for (auto [input, weapon, transform] : world.view<PlayerInput, Weapon, Transform>())
    {
        if (input.shoot && weapon.cooldown_timer <= 0.0f)
        {
            shoot(transform.position);
            LOG_DEBUG("Player shot.");
            weapon.cooldown_timer = weapon.cooldown_time;
        }
    }
}

void PlayerShootSystem::shoot(Vector2D position)
{
    AssetHandle<Texture> sprite =
        AssetsAPI::find_or_register<Texture>("assets/bullets/laserBlue01.png");
    AssetsAPI::load<Texture>(sprite);
    Entity bullet = EntityAPI::create_entity();
    auto &bullet_transform = bullet.add_component<Transform>();
    bullet_transform.position = position + Vector2D{45.0f, -55.0f};
    auto &bullet_velocity = bullet.add_component<Velocity>();
    bullet_velocity.linear = Vector2D{0.0f, -400.0f};
    bullet.add_component<Sprite>(sprite);
    bullet.add_component<Renderable>();
    bullet.add_component<OutOfBounds>();
}
