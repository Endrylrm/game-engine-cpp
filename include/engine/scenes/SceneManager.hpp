#pragma once
#include <functional>
#include <memory>
#include <ranges>
#include <string_view>
#include <unordered_map>

#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/core/string/StringHandle.hpp>

#include "Scene.hpp"
#include "SceneCommand.hpp"

using SceneBuilder = std::function<void(Scene &)>;

class SceneManager
{
public:
    template <typename Callback>
    void registerScene(std::string_view id, Callback &&callback)
    {
        LOG_DEBUG("Registered Scene '{}'...", id);
        scenes.try_emplace(StringHandle(id), std::forward<Callback>(callback));
    }

    void loadScene(std::string_view id);
    void loadSceneAdditive(std::string_view id);
    void unloadScene(std::string_view id);
    void unloadAllScenes();

    Scene *getActiveScene(std::string_view id) const;
    bool isActiveScene(std::string_view id) const;

    Scene *getMainScene();

    void onInit();
    void onPhysics(float fixedDeltaTime);
    void onPreUpdate();
    void onUpdate(float deltaTime);
    void onPostUpdate();
    void onRender(Renderer &renderer);
    void processLifecycle();
    void processCommands();

private:
    Scene *buildScene(std::string_view id);

    std::unordered_map<StringHandle, SceneBuilder, StringHandleHash> scenes{};
    std::vector<std::unique_ptr<Scene>> activeScenes{};
    std::vector<SceneCommand> pendingCommands{};
    Scene *mainScene{};
};
