#include "game/scenes/SceneFactory.hpp"

#include <random>

#include <engine/api/AssetsAPI.hpp>
#include <engine/assets/AssetHandle.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/ecs/components/BoxCollider.hpp>
#include <engine/ecs/components/Renderable.hpp>
#include <engine/ecs/components/SpriteRenderer.hpp>
#include <engine/ecs/components/Transform.hpp>
#include <engine/ecs/components/Velocity.hpp>
#include <engine/ecs/entities/EntityBuilder.hpp>
#include <engine/ecs/handle/Entity.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/systems/System.hpp>

#include <game/ecs/components/common/Health.hpp>
#include <game/ecs/components/common/ScreenClamp.hpp>
#include <game/ecs/components/common/Weapon.hpp>
#include <game/ecs/components/player/PlayerInput.hpp>
#include <game/ecs/systems/common/ScreenClampSystem.hpp>
#include <game/ecs/systems/common/WeaponCooldownSystem.hpp>
#include <game/ecs/systems/player/PlayerInputSystem.hpp>
#include <game/ecs/systems/player/PlayerMoveSystem.hpp>
#include <game/ecs/systems/player/PlayerShootSystem.hpp>

void SceneFactory::createMenuScene(Scene &scene)
{
    LOG_DEBUG("creating Menu Scene...");
    scene.createEntity();
}

void SceneFactory::createGameplayScene(Scene &scene)
{
    scene.addSystem<PlayerInputSystem>(SystemStage::Update, scene.getRegistry());
    scene.addSystem<PlayerMoveSystem>(SystemStage::Update, scene.getRegistry());
    scene.addSystem<WeaponCooldownSystem>(SystemStage::Update, scene.getRegistry());
    scene.addSystem<PlayerShootSystem>(SystemStage::Update, scene.getRegistry());
    scene.addSystem<ScreenClampSystem>(SystemStage::PostUpdate, scene.getRegistry());
    LOG_DEBUG("creating Gameplay Scene...");
    AssetHandle<Texture> sprite = AssetsAPI::load<Texture>("assets/player/playerShip1_blue.png");
    Entity player =
        EntityBuilder(scene)
            .addComponent<Transform>()
            .addComponent<Velocity>()
            .addComponent<SpriteRenderer>(sprite)
            .addComponent<Renderable>()
            .addComponent<Health>(5)
            .addComponent<Weapon>()
            .addComponent<BoxCollider>(Vector2D{99.0f, 75.0f}, Vector2D{0.0f, 0.0f}, false)
            .addComponent<ScreenClamp>(true, true)
            .addComponent<PlayerInput>()
            .build();

    LOG_DEBUG("Player has Sprite Renderer: {}", player.hasComponent<SpriteRenderer>());
    scene.createEntity();
}
