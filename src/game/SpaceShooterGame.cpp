#include "game/SpaceShooterGame.hpp"

#include "engine/api/ScenesAPI.hpp"

#include "game/scenes/GameplayScene.hpp"

void SpaceShooterGame::onInit()
{
    ScenesAPI::registerScene<GameplayScene>();
    ScenesAPI::loadScene<GameplayScene>();
}

void SpaceShooterGame::onShutdown() {}