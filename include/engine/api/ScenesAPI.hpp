#pragma once
#include <engine/api/ManagerAPI.hpp>
#include <engine/scenes/Scene.hpp>
#include <engine/scenes/SceneId.hpp>
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
        getManager().loadScene(name);
    }

    static void loadSceneAdditive(std::string_view name)
    {
        getManager().loadSceneAdditive(name);
    }

    static void unloadScene(std::string_view name)
    {
        getManager().unloadScene(name);
    }

    static Scene *getActiveScene(std::string_view name)
    {
        return getManager().getActiveScene(name);
    }

    static bool isActiveScene(std::string_view name)
    {
        return getManager().isActiveScene(name);
    }

    static bool setMainScene(std::string_view name)
    {
        return getManager().setMainScene(name);
    }

    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }
};
