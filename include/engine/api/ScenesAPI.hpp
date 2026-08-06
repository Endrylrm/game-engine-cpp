#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/scenes/Scene.hpp"
#include "engine/scenes/SceneConcept.hpp"
#include "engine/scenes/SceneManager.hpp"

class ScenesAPI : public ManagerAPI<SceneManager>
{
public:
    template <SceneConcept SceneType, typename... Args>
    static void registerScene(Args &&...args)
    {
        getManager().registerScene<SceneType>(std::forward<Args>(args)...);
    }

    template <SceneConcept SceneType>
    static void loadScene()
    {
        getManager().loadScene<SceneType>();
    }

    template <SceneConcept SceneType>
    static void loadSceneAdditive()
    {
        getManager().loadSceneAdditive<SceneType>();
    }

    template <SceneConcept SceneType>
    static void unloadScene()
    {
        getManager().unloadScene<SceneType>();
    }

    template <SceneConcept SceneType>
    static SceneType *getActiveScene()
    {
        return getManager().getActiveScene<SceneType>();
    }

    template <SceneConcept SceneType>
    static bool isActiveScene()
    {
        return getManager().isActiveScene<SceneType>();
    }

    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }
};