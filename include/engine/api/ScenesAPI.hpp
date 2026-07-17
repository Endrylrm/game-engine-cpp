#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/scenes/SceneManager.hpp"
#include "engine/scenes/Scene.hpp"

class ScenesAPI : public ManagerAPI<SceneManager>
{
public:
    template <std::derived_from<Scene> T, typename... Args>
    static void registerScene(Args &&...args)
    {
        getManager().registerScene<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    static void loadScene()
    {
        getManager().loadScene<T>();
    }

    template <typename T>
    static void loadSceneAdditive()
    {
        getManager().loadSceneAdditive<T>();
    }

    template <typename T>
    static void unloadScene()
    {
        getManager().unloadScene<T>();
    }

    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }
};