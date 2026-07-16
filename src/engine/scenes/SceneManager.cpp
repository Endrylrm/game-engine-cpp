#include "engine/scenes/SceneManager.hpp"

void SceneManager::onInit()
{
    if (currentScene)
        currentScene->init();
}

void SceneManager::onPhysics(float fixedDeltaTime)
{
    if (currentScene)
        currentScene->physics(fixedDeltaTime);
}

void SceneManager::onPreUpdate()
{
    if (currentScene)
        currentScene->preUpdate();
}

void SceneManager::onUpdate(float deltaTime)
{
    if (currentScene)
        currentScene->update(deltaTime);
}

void SceneManager::onPostUpdate()
{
    if (currentScene)
        currentScene->postUpdate();
}

void SceneManager::onRender(Renderer &renderer)
{
    if (currentScene)
        currentScene->render(renderer);
}

void SceneManager::processLifecycle()
{
    if (currentScene)
        currentScene->processLifecycle();
}
