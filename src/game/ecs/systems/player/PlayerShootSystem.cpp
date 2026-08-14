#include "game/ecs/systems/player/PlayerShootSystem.hpp"

#include <engine/api/AssetsAPI.hpp>
#include <engine/api/EntityAPI.hpp>
#include <engine/assets/AssetHandle.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/ecs/components/Renderable.hpp>
#include <engine/ecs/components/SpriteRenderer.hpp>
#include <engine/ecs/components/Transform.hpp>
#include <engine/ecs/components/Velocity.hpp>
#include <engine/ecs/handle/Entity.hpp>

#include <game/ecs/components/common/OutOfBounds.hpp>
#include <game/ecs/components/common/Weapon.hpp>
#include <game/ecs/components/player/PlayerInput.hpp>

void PlayerShootSystem::onUpdate(World &world, float deltaTime)
{
    for (auto [input, weapon, transform] : world.view<PlayerInput, Weapon, Transform>())
    {
        if (input.shoot && weapon.cooldownTimer <= 0.0f)
        {
            shoot(transform.position);
            LOG_DEBUG("Player shot.");
            weapon.cooldownTimer = weapon.cooldownTime;
        }
    }
}

void PlayerShootSystem::shoot(Vector2D position)
{
    AssetHandle<Texture> sprite = AssetsAPI::load<Texture>("assets/bullets/laserBlue01.png");
    Entity bullet = EntityAPI::createEntity();
    auto &bulletTransform = bullet.addComponent<Transform>();
    bulletTransform.position = position + Vector2D{45.0f, -55.0f};
    auto &bulletVelocity = bullet.addComponent<Velocity>();
    bulletVelocity.linear = Vector2D{0.0f, -300.0f};
    bullet.addComponent<SpriteRenderer>(sprite);
    bullet.addComponent<Renderable>();
    bullet.addComponent<OutOfBounds>();
}
