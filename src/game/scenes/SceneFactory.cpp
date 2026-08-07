#include "game/scenes/SceneFactory.hpp"

#include <engine/core/log/Log.hpp>

#include <game/factories/BulletFactory.hpp>
#include <game/factories/DirectorFactory.hpp>

void SceneFactory::createMenuScene(Scene &scene)
{
    LOG_DEBUG("creating Menu Scene...");
    scene.createEntity(DirectorFactory::create());
}

void SceneFactory::createGameplayScene(Scene &scene)
{
    LOG_DEBUG("creating Gameplay Scene...");
    scene.createEntity(DirectorFactory::create());
    scene.createEntity(BulletFactory::create());
}
