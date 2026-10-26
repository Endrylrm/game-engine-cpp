#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/scenes/Scene.hpp"
#include "engine/scenes/SceneId.hpp"
#include "engine/scenes/SceneLoadMode.hpp"
#include "engine/scenes/SceneManager.hpp"

class ScenesAPI : public ManagerAPI<SceneManager>
{
public:
    template <typename Callback>
    static SceneId register_scene(std::string_view name, Callback &&callback)
    {
        return get_manager().register_scene(name, std::forward<Callback>(callback));
    }

    static void load_scene(std::string_view name)
    {
        get_manager().load_scene(name, SceneLoadMode::Main);
    }

    static void load_scene_additive(std::string_view name)
    {
        get_manager().load_scene(name, SceneLoadMode::Additive);
    }

    static void load_scene_persistent(std::string_view name)
    {
        get_manager().load_scene(name, SceneLoadMode::Persistent);
    }

    static void unload_scene(std::string_view name)
    {
        get_manager().unload_scene(name);
    }

    static void unload_non_persistent_scenes()
    {
        get_manager().unload_non_persistent_scenes();
    }

    static void unload_all_scenes()
    {
        get_manager().unload_all_scenes();
    }

    static Scene *get_active_scene(std::string_view name)
    {
        return get_manager().get_active_scene(name);
    }

    static bool is_active_scene(std::string_view name)
    {
        return get_manager().is_active_scene(name);
    }

    static bool set_active_scene_as_main(std::string_view name)
    {
        return get_manager().set_active_scene_as_main(name);
    }

    static Scene *get_main_scene()
    {
        return get_manager().get_main_scene();
    }
};
