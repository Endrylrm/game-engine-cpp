#include "game/scenes/SceneFactory.hpp"

#include <random>

#include <engine/api/AssetsAPI.hpp>
#include <engine/assets/AssetHandle.hpp>
#include <engine/core/graphics/Texture.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/ecs/components/SpriteRenderer.hpp>
#include <engine/ecs/components/Transform.hpp>
#include <engine/ecs/components/Visible.hpp>
#include <engine/ecs/entities/EntityBuilder.hpp>
#include <engine/ecs/handle/Entity.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/systems/RenderSystem.hpp>

#include <game/ecs/components/common/Health.hpp>

void SceneFactory::createMenuScene(Scene &scene)
{
    LOG_DEBUG("creating Menu Scene...");
    scene.addSystem<RenderSystem>(SystemStage::Render, scene.getRegistry());
    scene.createEntity();
}

void SceneFactory::createGameplayScene(Scene &scene)
{
    LOG_DEBUG("creating Gameplay Scene...");
    scene.addSystem<RenderSystem>(SystemStage::Render, scene.getRegistry());
    AssetHandle<Texture> sprite = AssetsAPI::load<Texture>("assets/player/playerShip1_blue.png");
    Entity player = EntityBuilder(scene)
                        .addComponent<Transform>()
                        .addComponent<Visible>()
                        .addComponent<SpriteRenderer>(sprite)
                        .addComponent<Health>(5)
                        .build();

    LOG_DEBUG("Player has Sprite Renderer: {}", player.hasComponent<SpriteRenderer>());
    scene.createEntity();
}
