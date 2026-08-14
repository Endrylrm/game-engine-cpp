#pragma once
#include <memory>
#include <vector>

#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/helpers/Flags.hpp>
#include <engine/ecs/registry/systems/SystemEntry.hpp>
#include <engine/ecs/registry/systems/SystemRegistry.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/systems/System.hpp>

class World;

class SystemManager
{
public:
    explicit SystemManager(World &world) : world(world) {}

    template <std::derived_from<System> T, typename... Args>
    T &addSystem(Flags<SystemStage> stages, Args &&...args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);

        T &systemRef = *system;

        const auto id = SystemRegistry::getTypeId<T>();

        if (id >= systems.size())
            systems.resize(id + 1);

        if (systems[id].system)
            removeSystem<T>();

        registerSystem(*system, stages);

        systems[id] = {std::move(system), stages};

        return systemRef;
    }

    template <typename T>
    void removeSystem()
    {
        const auto id = SystemRegistry::getTypeId<T>();

        if (id >= systems.size() || !systems[id].system)
            return;

        auto &entry = systems[id];
        unregisterSystem(entry.system.get(), entry.stages);
        entry.system.reset();
        entry.stages.assign(SystemStage::None);
    }

    template <typename T>
    T *getSystem()
    {
        const auto id = SystemRegistry::getTypeId<T>();

        if (id >= systems.size())
            return nullptr;

        return static_cast<T *>(systems[id].system.get());
    }

    void init();
    void physics(float fixedDeltaTime);
    void preUpdate();
    void update(float deltaTime);
    void postUpdate();
    void render(Renderer &renderer);
    void unload();

private:
    void registerSystem(System &system, Flags<SystemStage> stages);
    void unregisterSystem(System *system, Flags<SystemStage> stages);

    World &world;

    std::vector<SystemEntry> systems{};
    std::vector<System *> physicsSystems{};
    std::vector<System *> preUpdateSystems{};
    std::vector<System *> updateSystems{};
    std::vector<System *> postUpdateSystems{};
    std::vector<System *> renderSystems{};
};
