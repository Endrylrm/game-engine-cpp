#include "game/scenes/GameplayScene.hpp"
#include "game/factories/BulletFactory.hpp"

void GameplayScene::onInit()
{
    gameManager.onStart();
    spawnEntityBlueprint(BulletFactory::create());
}

void GameplayScene::onPhysics(float fixedDeltaTime)
{
}

void GameplayScene::onPreUpdate()
{
}

void GameplayScene::onUpdate(float deltaTime)
{
    gameManager.onUpdate(deltaTime);
}

void GameplayScene::onPostUpdate()
{
}

void GameplayScene::onRender(Renderer &renderer)
{
}