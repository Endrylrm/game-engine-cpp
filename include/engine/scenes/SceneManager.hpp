#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "engine/scenes/Scene.hpp"
#include "engine/scenes/SceneRegistry.hpp"
#include "engine/scenes/SceneCommand.hpp"
#include "engine/core/graphics/Renderer.hpp"

class SceneManager
{
public:
    template <std::derived_from<Scene> T, typename... Args>
    void registerScene(Args &&...args)
    {
        SceneId id = SceneRegistry::GetId<T>();

        if (scenes.contains(id))
        {
            return;
        }

        scenes[id] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <std::derived_from<Scene> T>
    void loadScene()
    {
        unloadAllScenes();
        pendingCommands.push_back({SceneCommandType::Load, SceneRegistry::GetId<T>()});
    }

    template <std::derived_from<Scene> T>
    void loadSceneAdditive()
    {
        pendingCommands.push_back({SceneCommandType::LoadAdditive, SceneRegistry::GetId<T>()});
    }

    template <std::derived_from<Scene> T>
    void unloadScene()
    {
        pendingCommands.push_back({SceneCommandType::Unload, SceneRegistry::GetId<T>()});
    }

    void unloadAllScenes()
    {
        pendingCommands.push_back({SceneCommandType::UnloadAll, 0});
    }

    template <std::derived_from<Scene> T>
    T *getActiveScene() const
    {
        auto iter = scenes.find(SceneRegistry::GetId<T>());
        if (iter == scenes.end())
        {
            return nullptr;
        }

        Scene *scene = iter->second.get();

        auto vecIter = std::find(activeScenes.begin(), activeScenes.end(), scene);
        if (vecIter == activeScenes.end())
        {
            return nullptr;
        }

        return static_cast<T *>(scene);
    }

    template <std::derived_from<Scene> T>
    bool isActiveScene() const
    {
        auto iter = scenes.find(SceneRegistry::GetId<T>());
        if (iter == scenes.end())
        {
            return false;
        }

        Scene *scene = iter->second.get();

        auto vecIter = std::find(activeScenes.begin(), activeScenes.end(), scene);
        if (vecIter == activeScenes.end())
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
