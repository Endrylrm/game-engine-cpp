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
    template <SceneConcept SceneType, typename... Args>
    void registerScene(Args &&...args)
    {
        SceneId id = SceneRegistry::GetId<SceneType>();

        if (scenes.contains(id))
        {
            return;
        }

        scenes[id] = std::make_unique<SceneType>(std::forward<Args>(args)...);
    }

    template <SceneConcept SceneType>
    void loadScene()
    {
        unloadAllScenes();
        pendingCommands.push_back({SceneCommandType::Load, SceneRegistry::GetId<SceneType>()});
    }

    template <SceneConcept SceneType>
    void loadSceneAdditive()
    {
        pendingCommands.push_back({SceneCommandType::LoadAdditive, SceneRegistry::GetId<SceneType>()});
    }

    template <SceneConcept SceneType>
    void unloadScene()
    {
        pendingCommands.push_back({SceneCommandType::Unload, SceneRegistry::GetId<SceneType>()});
    }

    void unloadAllScenes()
    {
        pendingCommands.push_back({SceneCommandType::UnloadAll, 0});
    }

    template <SceneConcept SceneType>
    Scene *getActiveScene() const
    {
        auto iter = scenes.find(SceneRegistry::GetId<SceneType>());
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

        return static_cast<SceneType *>(scene);
    }

    template <SceneConcept SceneType>
    bool isActiveScene() const
    {
        auto iter = scenes.find(SceneRegistry::GetId<SceneType>());
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
    std::unordered_map<SceneId, std::unique_ptr<Scene>> scenes{};
    std::vector<Scene *> activeScenes{};
    std::vector<SceneCommand> pendingCommands{};
    Scene *mainScene{};
};
