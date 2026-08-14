#include "game/SpaceShooterGame.hpp"

#include <engine/api/ScenesAPI.hpp>

#include <game/scenes/SceneFactory.hpp>

void SpaceShooterGame::onInit()
{
    ScenesAPI::registerScene("Menu", SceneFactory::createMenuScene);
    ScenesAPI::registerScene("Gameplay", SceneFactory::createGameplayScene);
    ScenesAPI::loadScene("Gameplay");
}

void SpaceShooterGame::onShutdown() {}