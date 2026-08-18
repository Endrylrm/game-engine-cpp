#pragma once
#include <engine/api/ManagerAPI.hpp>
#include <engine/scenes/Scene.hpp>
#include <engine/scenes/SceneId.hpp>
#include <engine/scenes/SceneLoadMode.hpp>
#include <engine/scenes/SceneManager.hpp>

class ScenesAPI : public ManagerAPI<SceneManager>
{
public:
    template <typename Callback>
    static SceneId registerScene(std::string_view name, Callback &&callback)
    {
        return getManager().registerScene(name, std::forward<Callback>(callback));
    }

    static void loadScene(std::string_view name)
    {
        getManager().loadScene(name, SceneLoadMode::Main);
    }

    static void loadSceneAdditive(std::string_view name)
    {
        getManager().loadScene(name, SceneLoadMode::Additive);
    }

    static void loadScenePersistent(std::string_view name)
    {
        getManager().loadScene(name, SceneLoadMode::Persistent);
    }

    static void unloadScene(std::string_view name)
    {
        getManager().unloadScene(name);
    }

    static void unloadNonPersistentScenes()
    {
        getManager().unloadNonPersistentScenes();
    }

    static void unloadAllScenes()
    {
        getManager().unloadAllScenes();
    }

    static Scene *getActiveScene(std::string_view name)
    {
        return getManager().getActiveScene(name);
    }

    static bool isActiveScene(std::string_view name)
    {
        return getManager().isActiveScene(name);
    }

    static bool setActiveSceneAsMain(std::string_view name)
    {
        return getManager().setActiveSceneAsMain(name);
    }

    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }
};
