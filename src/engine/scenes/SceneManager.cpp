#include "engine/scenes/SceneManager.hpp"

void SceneManager::loadScene(SceneId id)
{
    LOG_INFO("Queued Load Scene '{}'...", id.value);
    unloadAllScenes();
    pendingCommands.push_back({SceneCommandType::Load, id});
}

void SceneManager::loadScene(std::string_view name)
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return;
    }

    loadScene(*id);
}

void SceneManager::loadSceneAdditive(SceneId id)
{
    LOG_INFO("Queued Load Scene '{}' (Additive)...", id.value);
    pendingCommands.push_back({SceneCommandType::LoadAdditive, id});
}

void SceneManager::loadSceneAdditive(std::string_view name)
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return;
    }

    loadSceneAdditive(*id);
}

void SceneManager::unloadScene(SceneId id)
{
    LOG_INFO("Queued Unload Scene '{}'...", id.value);
    pendingCommands.push_back({SceneCommandType::Unload, id});
}

void SceneManager::unloadScene(std::string_view name)
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return;
    }

    unloadScene(*id);
}

void SceneManager::unloadAllScenes()
{
    LOG_INFO("Queued Unload All Scenes...");
    pendingCommands.push_back({SceneCommandType::UnloadAll, {0}});
}

Scene *SceneManager::getActiveScene(SceneId id) const
{
    auto it = std::ranges::find(activeScenes, id, &Scene::getId);

    if (it == activeScenes.end())
    {
        return nullptr;
    }

    return it->get();
}

Scene *SceneManager::getActiveScene(std::string_view name) const
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not active.", name);
        return nullptr;
    }

    return getActiveScene(*id);
}

bool SceneManager::isActiveScene(SceneId id) const
{
    auto it = std::ranges::find(activeScenes, id, &Scene::getId);

    if (it == activeScenes.end())
    {
        return false;
    }

    return true;
}

bool SceneManager::isActiveScene(std::string_view name) const
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not active.", name);
        return false;
    }

    return isActiveScene(*id);
}

Scene *SceneManager::getMainScene()
{
    return mainScene;
}

Scene *SceneManager::buildScene(SceneId id)
{
    SceneBuilder builder = scenes.at(id);
    auto scene = std::make_unique<Scene>(id, world);
    builder(*scene);
    LOG_DEBUG("Created Scene instance '{}'.", id.value);
    Scene *scenePtr = scene.get();
    activeScenes.push_back(std::move(scene));
    return scenePtr;
}

std::optional<SceneId> SceneManager::findSceneId(std::string_view name) const
{
    auto it = sceneIds.find(StringHandle(name));

    if (it == sceneIds.end())
        return std::nullopt;

    return it->second;
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
            mainScene->load();
            LOG_INFO("Loaded Scene '{}'.", command.id.value);
            break;
        }
        case SceneCommandType::LoadAdditive:
        {
            auto *scene = buildScene(command.id);
            scene->load();
            LOG_INFO("Loaded Scene '{}' (Additive).", command.id.value);
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
            LOG_INFO("Unloaded Scene '{}'.", command.id.value);
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
