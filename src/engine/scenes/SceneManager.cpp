#include "engine/scenes/SceneManager.hpp"

void SceneManager::onInit()
{
}

void SceneManager::onPhysics(float fixedDeltaTime)
{
    for (auto *scene : activeScenes)
        scene->physics(fixedDeltaTime);
}

void SceneManager::onPreUpdate()
{
    for (auto *scene : activeScenes)
        scene->preUpdate();
}

void SceneManager::onUpdate(float deltaTime)
{
    for (auto *scene : activeScenes)
        scene->update(deltaTime);
}

void SceneManager::onPostUpdate()
{
    for (auto *scene : activeScenes)
        scene->postUpdate();
}

void SceneManager::onRender(Renderer &renderer)
{
    for (auto *scene : activeScenes)
        scene->render(renderer);
}

void SceneManager::processLifecycle()
{
    for (auto *scene : activeScenes)
        scene->processLifecycle();
}

void SceneManager::processCommands()
{
    for (auto &command : pendingCommands)
    {
        switch (command.type)
        {
        case SceneCommandType::Load:
        {
            if (!activeScenes.empty())
                activeScenes.clear();

            auto *scene = scenes.at(command.id).get();
            mainScene = scene;
            activeScenes.push_back(scene);
            scene->init();
            break;
        }
        case SceneCommandType::LoadAdditive:
        {
            auto *scene = scenes.at(command.id).get();
            activeScenes.push_back(scene);
            scene->init();
            break;
        }
        case SceneCommandType::Unload:
        {
            break;
        }
        default:
            break;
        }
    }
    pendingCommands.clear();
}
