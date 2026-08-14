#include "game/SpaceShooterGame.hpp"

#include <engine/api/ScenesAPI.hpp>
#include <engine/api/WorldAPI.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>

#include <game/ecs/systems/common/OutOfBoundsSystem.hpp>
#include <game/ecs/systems/common/ScreenClampSystem.hpp>
#include <game/ecs/systems/common/WeaponCooldownSystem.hpp>
#include <game/ecs/systems/player/PlayerInputSystem.hpp>
#include <game/ecs/systems/player/PlayerMoveSystem.hpp>
#include <game/ecs/systems/player/PlayerShootSystem.hpp>
#include <game/scenes/SceneFactory.hpp>

void SpaceShooterGame::onInit()
{
    WorldAPI::addSystem<PlayerInputSystem>(SystemStage::Update);
    WorldAPI::addSystem<PlayerMoveSystem>(SystemStage::Update);
    WorldAPI::addSystem<WeaponCooldownSystem>(SystemStage::Update);
    WorldAPI::addSystem<PlayerShootSystem>(SystemStage::Update);
    WorldAPI::addSystem<OutOfBoundsSystem>(SystemStage::Update);
    WorldAPI::addSystem<ScreenClampSystem>(SystemStage::PostUpdate);

    ScenesAPI::registerScene("Menu", SceneFactory::createMenuScene);
    ScenesAPI::registerScene("Gameplay", SceneFactory::createGameplayScene);
    ScenesAPI::loadScene("Gameplay");
}

void SpaceShooterGame::onShutdown() {}