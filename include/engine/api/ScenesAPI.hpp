#pragma once
#include <engine/api/ManagerAPI.hpp>
#include <engine/scenes/Scene.hpp>
#include <engine/scenes/SceneManager.hpp>

class ScenesAPI : public ManagerAPI<SceneManager>
{
public:
    template <typename Callback>
    static void registerScene(std::string_view id, Callback &&callback)
    {
        getManager().registerScene(id, std::forward<Callback>(callback));
    }

    static void loadScene(std::string_view id)
    {
        getManager().loadScene(id);
    }

    static void loadSceneAdditive(std::string_view id)
    {
        getManager().loadSceneAdditive(id);
    }

    static void unloadScene(std::string_view id)
    {
        getManager().unloadScene(id);
    }

    static Scene *getActiveScene(std::string_view id)
    {
        return getManager().getActiveScene(id);
    }

    static bool isActiveScene(std::string_view id)
    {
        return getManager().isActiveScene(id);
    }

    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }
};