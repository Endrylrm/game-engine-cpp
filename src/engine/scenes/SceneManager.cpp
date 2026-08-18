#include "engine/scenes/SceneManager.hpp"

void SceneManager::loadScene(SceneId id, SceneLoadMode mode)
{
    switch (mode)
    {
    case SceneLoadMode::Main:
    {
        unloadNonPersistentScenes();
        pendingCommands.push_back({SceneCommandType::Load, id});
        LOG_INFO("Queued Load Scene '{}'...", id.value);
        break;
    }
    case SceneLoadMode::Additive:
    {
        pendingCommands.push_back({SceneCommandType::LoadAdditive, id});
        LOG_INFO("Queued Load Scene '{}' (Additive)...", id.value);
        break;
    }
    case SceneLoadMode::Persistent:
    {
        pendingCommands.push_back({SceneCommandType::LoadPersistent, id});
        LOG_INFO("Queued Load Scene '{}' (Persistent)...", id.value);
        break;
    }
    default:
        LOG_ERROR("Unknown Scene command type...");
        break;
    }
}

void SceneManager::loadScene(std::string_view name, SceneLoadMode mode)
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return;
    }

    loadScene(*id, mode);
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

void SceneManager::unloadNonPersistentScenes()
{
    LOG_INFO("Queued Unload All non persistent Scenes...");
    pendingCommands.push_back({SceneCommandType::UnloadNonPersistent, {0}});
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
        LOG_ERROR("Scene '{}' is not active.", id.value);
        return nullptr;
    }

    return it->get();
}

Scene *SceneManager::getActiveScene(std::string_view name) const
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return nullptr;
    }

    return getActiveScene(*id);
}

bool SceneManager::isActiveScene(SceneId id) const
{
    auto it = std::ranges::find(activeScenes, id, &Scene::getId);

    if (it == activeScenes.end())
    {
        LOG_ERROR("Scene '{}' is not active.", id.value);
        return false;
    }

    return true;
}

bool SceneManager::isActiveScene(std::string_view name) const
{
    auto id = findSceneId(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return false;
    }

    return isActiveScene(*id);
}

Scene *SceneManager::getMainScene()
{
    return mainScene;
}

bool SceneManager::setMainScene(SceneId id)
{
    Scene *scene = getActiveScene(id);

    if (!scene)
    {
        return false;
    }

    mainScene = scene;
    return true;
}

bool SceneManager::setMainScene(std::string_view name)
{
    Scene *scene = getActiveScene(name);

    if (!scene)
    {
        return false;
    }

    mainScene = scene;
    return true;
}

Scene *SceneManager::getPersistentScene()
{
    return persistentScene;
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
        case SceneCommandType::LoadPersistent:
        {
            if (persistentScene)
                persistentScene->unload();

            std::erase_if(
                activeScenes,
                [&](const auto &scenePtr) { return scenePtr.get() == persistentScene; }
            );

            persistentScene = buildScene(command.id);
            persistentScene->load();
            LOG_INFO("Loaded Scene '{}' (Persistent).", command.id.value);
            break;
        }
        case SceneCommandType::Unload:
        {
            auto *scene = getActiveScene(command.id);

            if (!scene)
            {
                LOG_WARNING("Scene '{}' is not loaded.", command.id.value);
                break;
            }

            if (mainScene == scene)
                mainScene = nullptr;

            if (persistentScene == scene)
                persistentScene = nullptr;

            scene->unload();

            std::erase_if(
                activeScenes, [scene](const auto &scenePtr) { return scenePtr.get() == scene; }
            );

            LOG_INFO("Unloaded Scene '{}'.", command.id.value);
            break;
        }
        case SceneCommandType::UnloadNonPersistent:
        {
            for (auto &scene : activeScenes)
            {
                if (scene.get() != persistentScene)
                    scene->unload();
            }

            std::erase_if(
                activeScenes,
                [&](const auto &scenePtr) { return scenePtr.get() != persistentScene; }
            );
            LOG_INFO("Unloaded All non persistent Scenes...");
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
