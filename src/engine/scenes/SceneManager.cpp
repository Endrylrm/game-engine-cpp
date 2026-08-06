#include "engine/scenes/SceneManager.hpp"

void SceneManager::onInit() {}

void SceneManager::onPhysics(float fixedDeltaTime)
{
    for (auto &scene : activeScenes)
        scene->physics(fixedDeltaTime);
}

void SceneManager::onPreUpdate()
{
    for (auto &scene : activeScenes)
        scene->preUpdate();
}

void SceneManager::onUpdate(float deltaTime)
{
    for (auto &scene : activeScenes)
        scene->update(deltaTime);
}

void SceneManager::onPostUpdate()
{
    for (auto &scene : activeScenes)
        scene->postUpdate();
}

void SceneManager::onRender(Renderer &renderer)
{
    for (auto &scene : activeScenes)
        scene->render(renderer);
}

void SceneManager::processLifecycle()
{
    for (auto &scene : activeScenes)
        scene->processLifecycle();
}

void SceneManager::loadScene(std::string_view id)
{
    LOG_INFO("Queued Load Scene '{}'...", id);
    unloadAllScenes();
    pendingCommands.push_back({SceneCommandType::Load, StringHandle(id)});
}

void SceneManager::loadSceneAdditive(std::string_view id)
{
    LOG_INFO("Queued Load Scene '{}' (Additive)...", id);
    pendingCommands.push_back({SceneCommandType::LoadAdditive, StringHandle(id)});
}

void SceneManager::unloadScene(std::string_view id)
{
    LOG_INFO("Queued Unload Scene '{}'...", id);
    pendingCommands.push_back({SceneCommandType::Unload, StringHandle(id)});
}

void SceneManager::unloadAllScenes()
{
    LOG_INFO("Queued Unload All Scenes...");
    pendingCommands.push_back({SceneCommandType::UnloadAll, StringHandle("")});
}

Scene *SceneManager::getActiveScene(std::string_view id) const
{
    auto it = std::ranges::find(activeScenes, StringHandle(id), &Scene::name);

    if (it == activeScenes.end())
    {
        return nullptr;
    }

    return it->get();
}

bool SceneManager::isActiveScene(std::string_view id) const
{
    auto it = std::ranges::find(activeScenes, StringHandle(id), &Scene::name);

    if (it == activeScenes.end())
    {
        return false;
    }

    return true;
}

Scene *SceneManager::getMainScene()
{
    return mainScene;
}

Scene *SceneManager::buildScene(std::string_view id)
{
    SceneBuilder builder = scenes.at(StringHandle(id));
    auto scene = std::make_unique<Scene>();
    scene->name = id;
    builder(*scene);
    LOG_DEBUG("Created Scene instance '{}'.", id);
    Scene *scenePtr = scene.get();
    activeScenes.push_back(std::move(scene));
    scenePtr->init();
    return scenePtr;
}

void SceneManager::processCommands()
{
    if (pendingCommands.size() > 0)
    {
        LOG_DEBUG("Processing {} commands...", pendingCommands.size());
    }

    for (auto &command : pendingCommands)
    {
        switch (command.type)
        {
        case SceneCommandType::Load:
        {
            if (!activeScenes.empty())
            {
                for (auto &scene : activeScenes)
                {
                    scene->unload();
                }
                activeScenes.clear();
            }

            mainScene = buildScene(command.id);
            LOG_INFO("Loaded Scene '{}'.", command.id.text());
            break;
        }
        case SceneCommandType::LoadAdditive:
        {
            buildScene(command.id);
            LOG_INFO("Loaded Scene '{}' (Additive).", command.id.text());
            break;
        }
        case SceneCommandType::Unload:
        {
            auto *scene = getActiveScene(command.id);
            if (mainScene == scene)
                mainScene = nullptr;
            scene->unload();
            std::erase_if(
                activeScenes, [scene](const auto &scenePtr) { return scenePtr.get() == scene; }
            );
            LOG_INFO("Unloaded Scene '{}'.", command.id.text());
            break;
        }
        case SceneCommandType::UnloadAll:
        {
            for (auto &scene : activeScenes)
            {
                scene->unload();
            }
            activeScenes.clear();
            LOG_INFO("Unloaded All Scenes...");
            break;
        }
        default:
            break;
        }
    }
    pendingCommands.clear();
}
