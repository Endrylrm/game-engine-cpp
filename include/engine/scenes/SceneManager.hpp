#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "engine/scenes/Scene.hpp"
#include "engine/scenes/SceneRegistry.hpp"
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

    template <typename T>
    void changeScene()
    {
        currentScene = scenes.at(SceneRegistry::GetId<T>()).get();
        currentScene->init();
    }

    Scene *getCurrentScene()
    {
        return currentScene;
    }

    void onInit();
    void onPhysics(float fixedDeltaTime);
    void onPreUpdate();
    void onUpdate(float deltaTime);
    void onPostUpdate();
    void onRender(Renderer &renderer);
    void processLifecycle();

private:
    std::unordered_map<SceneId, std::unique_ptr<Scene>> scenes;
    Scene *currentScene = nullptr;
};
