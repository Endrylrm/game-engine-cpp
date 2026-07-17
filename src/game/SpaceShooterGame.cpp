#include "game/SpaceShooterGame.hpp"
#include "game/scenes/GameplayScene.hpp"
#include "engine/api/ScenesAPI.hpp"

void SpaceShooterGame::onInit()
{
    ScenesAPI::registerScene<GameplayScene>();
    ScenesAPI::loadScene<GameplayScene>();
}

void SpaceShooterGame::onShutdown()
{
}