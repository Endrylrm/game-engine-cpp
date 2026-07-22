#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "engine/scenes/Scene.hpp"
#include "engine/scenes/SceneRegistry.hpp"
#include "engine/scenes/SceneCommand.hpp"
#include "engine/scenes/SceneConcept.hpp"
#include "engine/core/graphics/Renderer.hpp"

class SceneManager
{
public:
    template <SceneConcept Scene, typename... Args>
    void registerScene(Args &&...args)
    {
        SceneId id = SceneRegistry::GetId<Scene>();

        if (scenes.contains(id))
        {
            return;
        }

        scenes[id] = std::make_unique<Scene>(std::forward<Args>(args)...);
    }

    template <SceneConcept Scene>
    void loadScene()
    {
        unloadAllScenes();
        pendingCommands.push_back({SceneCommandType::Load, SceneRegistry::GetId<Scene>()});
    }

    template <SceneConcept Scene>
    void loadSceneAdditive()
    {
        pendingCommands.push_back({SceneCommandType::LoadAdditive, SceneRegistry::GetId<Scene>()});
    }

    template <SceneConcept Scene>
    void unloadScene()
    {
        pendingCommands.push_back({SceneCommandType::Unload, SceneRegistry::GetId<Scene>()});
    }

    void unloadAllScenes()
    {
        pendingCommands.push_back({SceneCommandType::UnloadAll, 0});
    }

    template <SceneConcept Scene>
    Scene *getActiveScene() const
    {
        auto iter = scenes.find(SceneRegistry::GetId<Scene>());
        if (iter == scenes.end())
        {
            return nullptr;
        }

        Scene *scene = iter->second.get();

        auto sceneIter = std::find(activeScenes.begin(), activeScenes.end(), scene);
        if (sceneIter == activeScenes.end())
        {
            return nullptr;
        }

        return static_cast<Scene *>(scene);
    }

    template <SceneConcept Scene>
    bool isActiveScene() const
    {
        auto iter = scenes.find(SceneRegistry::GetId<Scene>());
        if (iter == scenes.end())
        {
            return false;
        }

        Scene *scene = iter->second.get();

        auto sceneIter = std::find(activeScenes.begin(), activeScenes.end(), scene);
        if (sceneIter == activeScenes.end())
        {
            return false;
        }

        return true;
    }

    Scene *getMainScene()
    {
        return mainScene;
    }

    void onInit();
    void onPhysics(float fixedDeltaTime);
    void onPreUpdate();
    void onUpdate(float deltaTime);
    void onPostUpdate();
    void onRender(Renderer &renderer);
    void processLifecycle();
    void processCommands();

private:
    std::unordered_map<SceneId, std::unique_ptr<Scene>> scenes;
    std::vector<Scene *> activeScenes;
    std::vector<SceneCommand> pendingCommands;
    Scene *mainScene = nullptr;
};
