#pragma once
#include <memory>
#include <vector>

#include "engine/core/helpers/Flags.hpp"
#include "engine/core/log/Log.hpp"
#include "engine/core/log/TypeName.hpp"
#include "engine/ecs/registry/systems/SystemEntry.hpp"
#include "engine/ecs/registry/systems/SystemRegistry.hpp"
#include "engine/ecs/registry/systems/SystemStage.hpp"
#include "engine/ecs/systems/System.hpp"
#include "engine/renderer/Renderer.hpp"

class World;

class SystemManager
{
public:
    explicit SystemManager(World &world) : world(world) {}

    template <std::derived_from<System> T, typename... Args>
    T &add_system(Flags<SystemStage> stages, Args &&...args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);

        T &systemRef = *system;

        const auto id = SystemRegistry::get_type_id<T>();

        if (id >= systems.size())
            systems.resize(id + 1);

        if (systems[id].system)
            remove_system<T>();

        register_system(*system, stages);
        LOG_DEBUG("System added: {}", get_type_name<T>());

        systems[id] = {std::move(system), stages};

        return systemRef;
    }

    template <typename T>
    void remove_system()
    {
        const auto id = SystemRegistry::get_type_id<T>();

        if (id >= systems.size() || !systems[id].system)
            return;

        auto &entry = systems[id];
        unregister_system(entry.system.get(), entry.stages);
        LOG_DEBUG("System removed: {}", get_type_name<T>());
        entry.system.reset();
        entry.stages.assign(SystemStage::None);
    }

    template <typename T>
    T *get_system()
    {
        const auto id = SystemRegistry::get_type_id<T>();

        if (id >= systems.size())
            return nullptr;

        LOG_DEBUG("got System: {}", get_type_name<T>());
        return static_cast<T *>(systems[id].system.get());
    }

    void init();
    void physics(float fixed_delta_time);
    void pre_update();
    void update(float delta_time);
    void post_update();
    void render(Renderer &renderer);
    void unload();

private:
    void register_system(System &system, Flags<SystemStage> stages);
    void unregister_system(System *system, Flags<SystemStage> stages);

    World &world;

    std::vector<SystemEntry> systems{};
    std::vector<System *> physics_systems{};
    std::vector<System *> pre_update_systems{};
    std::vector<System *> update_systems{};
    std::vector<System *> post_update_systems{};
    std::vector<System *> render_systems{};
};
