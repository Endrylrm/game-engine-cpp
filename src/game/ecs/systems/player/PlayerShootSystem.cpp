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

void PlayerShootSystem::onUpdate(float deltaTime)
{
    for (auto [input, weapon, transform] : registry.view<PlayerInput, Weapon, Transform>())
    {
        if (input.shoot && weapon.cooldownTimer <= 0.0f)
        {
            shoot(transform.position.x, transform.position.y);
            LOG_DEBUG("Player shot.");
            weapon.cooldownTimer = weapon.cooldownTime;
        }
    }
}

void PlayerShootSystem::shoot(float x, float y)
{
    AssetHandle<Texture> sprite = AssetsAPI::load<Texture>("assets/bullets/laserBlue01.png");
    Entity bullet = EntityAPI::createEntity();
    auto &bulletTransform = bullet.addComponent<Transform>();
    bulletTransform.position.x = x + 45.0f;
    bulletTransform.position.y = y - 55.0f;
    auto &bulletVelocity = bullet.addComponent<Velocity>();
    bulletVelocity.linear.y = -1.0f * 300.0f;
    bullet.addComponent<SpriteRenderer>(sprite);
    bullet.addComponent<Renderable>();
    bullet.addComponent<OutOfBounds>();
}
