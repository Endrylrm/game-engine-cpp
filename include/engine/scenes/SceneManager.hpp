#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <ranges>
#include <string_view>
#include <unordered_map>

#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/log/Log.hpp>
#include <engine/core/string/StringHandle.hpp>
#include <engine/ecs/world/World.hpp>

#include "Scene.hpp"
#include "SceneCommand.hpp"
#include "SceneId.hpp"
#include "SceneLoadMode.hpp"

using SceneBuilder = std::function<void(Scene &)>;

class SceneManager
{
public:
    SceneManager(World &world) : world(world) {}
    template <typename Callback>
    SceneId registerScene(std::string_view name, Callback &&callback)
    {
        const SceneId id{nextSceneId++};
        LOG_DEBUG("Registered Scene '{}'...", id.value);

        scenes.try_emplace(id, std::forward<Callback>(callback));
        sceneIds.emplace(StringHandle(name), id);

        return id;
    }

    void loadScene(SceneId id, SceneLoadMode mode);
    void loadScene(std::string_view name, SceneLoadMode mode);

    void unloadScene(SceneId id);
    void unloadScene(std::string_view name);
    void unloadNonPersistentScenes();
    void unloadAllScenes();

    Scene *getActiveScene(SceneId id) const;
    Scene *getActiveScene(std::string_view name) const;

    bool isActiveScene(SceneId id) const;
    bool isActiveScene(std::string_view name) const;

    Scene *getMainScene();
    bool setActiveSceneAsMain(SceneId id);
    bool setActiveSceneAsMain(std::string_view name);

    Scene *getPersistentScene();

    void processCommands();

private:
    Scene *buildScene(SceneId id);
    std::optional<SceneId> findSceneId(std::string_view name) const;

    uint32_t nextSceneId{0};
    std::unordered_map<SceneId, SceneBuilder, SceneIdHash> scenes{};
    std::unordered_map<StringHandle, SceneId, StringHandleHash> sceneIds{};
    std::vector<std::unique_ptr<Scene>> activeScenes{};
    std::vector<SceneCommand> pendingCommands{};
    Scene *mainScene{};
    Scene *persistentScene{};
    World &world;
};
