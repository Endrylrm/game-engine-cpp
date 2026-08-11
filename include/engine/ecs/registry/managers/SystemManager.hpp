#pragma once
#include <memory>
#include <vector>

#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/helpers/Flags.hpp>
#include <engine/ecs/registry/systems/SystemRegistry.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/systems/System.hpp>

class SystemManager
{
public:
    template <std::derived_from<System> T, typename... Args>
    T &addSystem(Flags<SystemStage> stages, Args &&...args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);

        T &systemRef = *system;

        const auto id = SystemRegistry::getTypeId<T>();

        if (id >= systems.size())
            systems.resize(id + 1);

        registerSystem(*system, stages);

        systems[id] = std::move(system);

        return systemRef;
    }

    template <typename T>
    T *getSystem()
    {
        const auto id = SystemRegistry::getTypeId<T>();

        if (id >= systems.size())
            return nullptr;

        return static_cast<T *>(systems[id].get());
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

    std::vector<std::unique_ptr<System>> systems{};
    std::vector<System *> physicsSystems{};
    std::vector<System *> preUpdateSystems{};
    std::vector<System *> updateSystems{};
    std::vector<System *> postUpdateSystems{};
    std::vector<System *> renderSystems{};
};
