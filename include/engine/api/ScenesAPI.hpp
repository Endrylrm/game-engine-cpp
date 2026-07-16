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
    static void changeScene()
    {
        getManager().changeScene<T>();
    }

    static Scene *getCurrentScene()
    {
        return getManager().getCurrentScene();
    }
};