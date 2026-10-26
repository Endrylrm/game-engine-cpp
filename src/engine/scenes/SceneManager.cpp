#include "engine/scenes/SceneManager.hpp"

void SceneManager::load_scene(SceneId id, SceneLoadMode mode)
{
    switch (mode)
    {
    case SceneLoadMode::Main:
    {
        unload_non_persistent_scenes();
        pending_commands.push_back({SceneCommandType::Load, id});
        LOG_INFO("Queued Load Scene '{}'...", id.index);
        break;
    }
    case SceneLoadMode::Additive:
    {
        pending_commands.push_back({SceneCommandType::LoadAdditive, id});
        LOG_INFO("Queued Load Scene '{}' (Additive)...", id.index);
        break;
    }
    case SceneLoadMode::Persistent:
    {
        pending_commands.push_back({SceneCommandType::LoadPersistent, id});
        LOG_INFO("Queued Load Scene '{}' (Persistent)...", id.index);
        break;
    }
    default:
        LOG_ERROR("Unknown Scene command type...");
        break;
    }
}

void SceneManager::load_scene(std::string_view name, SceneLoadMode mode)
{
    auto id = find_scene_id(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return;
    }

    load_scene(*id, mode);
}

void SceneManager::unload_scene(SceneId id)
{
    LOG_INFO("Queued Unload Scene '{}'...", id.index);
    pending_commands.push_back({SceneCommandType::Unload, id});
}

void SceneManager::unload_scene(std::string_view name)
{
    auto id = find_scene_id(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return;
    }

    unload_scene(*id);
}

void SceneManager::unload_non_persistent_scenes()
{
    LOG_INFO("Queued Unload All non persistent Scenes...");
    pending_commands.push_back({SceneCommandType::UnloadNonPersistent, {0}});
}

void SceneManager::unload_all_scenes()
{
    LOG_INFO("Queued Unload All Scenes...");
    pending_commands.push_back({SceneCommandType::UnloadAll, {0}});
}

Scene *SceneManager::get_active_scene(SceneId id) const
{
    auto it = std::ranges::find(active_scenes, id, &Scene::get_id);

    if (it == active_scenes.end())
    {
        LOG_ERROR("Scene '{}' is not active.", id.index);
        return nullptr;
    }

    return it->get();
}

Scene *SceneManager::get_active_scene(std::string_view name) const
{
    auto id = find_scene_id(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return nullptr;
    }

    return get_active_scene(*id);
}

bool SceneManager::is_active_scene(SceneId id) const
{
    auto it = std::ranges::find(active_scenes, id, &Scene::get_id);

    if (it == active_scenes.end())
    {
        LOG_ERROR("Scene '{}' is not active.", id.index);
        return false;
    }

    return true;
}

bool SceneManager::is_active_scene(std::string_view name) const
{
    auto id = find_scene_id(name);

    if (!id)
    {
        LOG_ERROR("Scene '{}' is not registered.", name);
        return false;
    }

    return is_active_scene(*id);
}

Scene *SceneManager::get_main_scene()
{
    return main_scene;
}

bool SceneManager::set_active_scene_as_main(SceneId id)
{
    Scene *scene = get_active_scene(id);

    if (!scene)
    {
        return false;
    }

    main_scene = scene;
    return true;
}

bool SceneManager::set_active_scene_as_main(std::string_view name)
{
    Scene *scene = get_active_scene(name);

    if (!scene)
    {
        return false;
    }

    main_scene = scene;
    return true;
}

Scene *SceneManager::get_persistent_scene()
{
    return persistent_scene;
}

Scene *SceneManager::build_scene(SceneId id)
{
    SceneBuilder builder = scenes.at(id);
    auto scene = std::make_unique<Scene>(id, world);
    builder(*scene);
    LOG_DEBUG("Created Scene instance '{}'.", id.index);
    Scene *scene_ptr = scene.get();
    active_scenes.push_back(std::move(scene));
    return scene_ptr;
}

std::optional<SceneId> SceneManager::find_scene_id(std::string_view name) const
{
    auto it = scene_ids.find(StringHandle(name));

    if (it == scene_ids.end())
        return std::nullopt;

    return it->second;
}

void SceneManager::process_commands()
{
    if (pending_commands.size() > 0)
    {
        LOG_DEBUG("Processing {} commands...", pending_commands.size());
    }

    for (auto &command : pending_commands)
    {
        switch (command.type)
        {
        case SceneCommandType::Load:
        {
            main_scene = build_scene(command.id);
            main_scene->load();
            LOG_INFO("Loaded Scene '{}'.", command.id.index);
            break;
        }
        case SceneCommandType::LoadAdditive:
        {
            auto *scene = build_scene(command.id);
            scene->load();
            LOG_INFO("Loaded Scene '{}' (Additive).", command.id.index);
            break;
        }
        case SceneCommandType::LoadPersistent:
        {
            if (persistent_scene)
                persistent_scene->unload();

            std::erase_if(
                active_scenes,
                [&](const auto &scenePtr) { return scenePtr.get() == persistent_scene; }
            );

            persistent_scene = build_scene(command.id);
            persistent_scene->load();
            LOG_INFO("Loaded Scene '{}' (Persistent).", command.id.index);
            break;
        }
        case SceneCommandType::Unload:
        {
            auto *scene = get_active_scene(command.id);

            if (!scene)
            {
                LOG_WARNING("Scene '{}' is not loaded.", command.id.index);
                break;
            }

            if (main_scene == scene)
                main_scene = nullptr;

            if (persistent_scene == scene)
                persistent_scene = nullptr;

            scene->unload();

            std::erase_if(
                active_scenes, [scene](const auto &scenePtr) { return scenePtr.get() == scene; }
            );

            LOG_INFO("Unloaded Scene '{}'.", command.id.index);
            break;
        }
        case SceneCommandType::UnloadNonPersistent:
        {
            for (auto &scene : active_scenes)
            {
                if (scene.get() != persistent_scene)
                    scene->unload();
            }

            std::erase_if(
                active_scenes,
                [&](const auto &scenePtr) { return scenePtr.get() != persistent_scene; }
            );
            LOG_INFO("Unloaded All non persistent Scenes...");
            break;
        }
        case SceneCommandType::UnloadAll:
        {
            for (auto &scene : active_scenes)
            {
                scene->unload();
            }

            active_scenes.clear();
            LOG_INFO("Unloaded All Scenes...");
            break;
        }
        default:
            break;
        }
    }
    pending_commands.clear();
}
