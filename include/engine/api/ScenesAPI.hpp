#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/scenes/SceneManager.hpp"
#include "engine/scenes/Scene.hpp"
#include "engine/scenes/SceneConcept.hpp"

class ScenesAPI : public ManagerAPI<SceneManager>
{
public:
    template <SceneConcept Scene, typename... Args>
    static void registerScene(Args &&...args)
    {
        getManager().registerScene<Scene>(std::forward<Args>(args)...);
    }

    template <SceneConcept Scene>
    static void loadScene()
    {
        getManager().loadScene<Scene>();
    }

    template <SceneConcept Scene>
    static void loadSceneAdditive()
    {
        getManager().loadSceneAdditive<Scene>();
    }

    template <SceneConcept Scene>
    static void unloadScene()
    {
        getManager().unloadScene<Scene>();
    }

    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }
};