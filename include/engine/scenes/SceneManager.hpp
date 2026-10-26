#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>

#include "engine/core/log/Log.hpp"
#include "engine/core/string/StringHandle.hpp"
#include "engine/ecs/world/World.hpp"

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
    SceneId register_scene(std::string_view name, Callback &&callback)
    {
        const SceneId ID{next_scene_id++};
        LOG_DEBUG("Registered Scene '{}'...", ID.index);

        scenes.try_emplace(ID, std::forward<Callback>(callback));
        scene_ids.emplace(StringHandle(name), ID);

        return ID;
    }

    void load_scene(SceneId id, SceneLoadMode mode);
    void load_scene(std::string_view name, SceneLoadMode mode);

    void unload_scene(SceneId id);
    void unload_scene(std::string_view name);
    void unload_non_persistent_scenes();
    void unload_all_scenes();

    Scene *get_active_scene(SceneId id) const;
    Scene *get_active_scene(std::string_view name) const;

    bool is_active_scene(SceneId id) const;
    bool is_active_scene(std::string_view name) const;

    Scene *get_main_scene();
    bool set_active_scene_as_main(SceneId id);
    bool set_active_scene_as_main(std::string_view name);

    Scene *get_persistent_scene();

    void process_commands();

private:
    Scene *build_scene(SceneId id);
    std::optional<SceneId> find_scene_id(std::string_view name) const;

    uint32_t next_scene_id{0};
    std::unordered_map<SceneId, SceneBuilder> scenes{};
    std::unordered_map<StringHandle, SceneId, StringHandleHash> scene_ids{};
    std::vector<std::unique_ptr<Scene>> active_scenes{};
    std::vector<SceneCommand> pending_commands{};
    Scene *main_scene{};
    Scene *persistent_scene{};
    World &world;
};
