#pragma once
#include <functional>
#include <memory>

#include <engine/core/events/EventBus.hpp>
#include <engine/core/graphics/Renderer.hpp>
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/ecs/registry/managers/SystemManager.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/registry/views/View.hpp>
#include <engine/ecs/systems/System.hpp>
#include <engine/scenes/SceneId.hpp>

class Entity;

class World
{
public:
    void init();
    void events();
    void physics(float fixedDeltaTime);
    void preUpdate();
    void update(float deltaTime);
    void postUpdate();
    void render(Renderer &renderer);
    void processLifecycle();
    void unload();

    Entity createEntity();
    void destroyEntity(EntityId entity);
    void destroySceneEntities(SceneId id);

    template <typename T, typename... Args>
    T &addComponent(EntityId entity, Args &&...args)
    {
        return registry.addComponent<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T &addComponent(EntityId entity, T &&value)
    {
        return registry.addComponent<T>(entity, std::move(value));
    }

    template <typename T>
    T &getComponent(EntityId entity)
    {
        return registry.getComponent<T>(entity);
    }

    template <typename T>
    T &getOrAddComponent(EntityId entity)
    {
        return registry.getOrAddComponent<T>(entity);
    }

    template <typename T>
    T *tryGetComponent(EntityId entity)
    {
        return registry.tryGetComponent<T>(entity);
    }

    template <typename T>
    bool hasComponent(EntityId entity)
    {
        return registry.hasComponent<T>(entity);
    }

    template <typename T>
    void removeComponent(EntityId entity)
    {
        registry.removeComponent<T>(entity);
    }

    void removeAllComponents(EntityId entity);

    template <typename... Components>
    View<Components...> view()
    {
        return registry.view<Components...>();
    }

    template <std::derived_from<System> T, typename... Args>
    T &addSystem(Flags<SystemStage> stages, Args &&...args)
    {
        return systemManager.addSystem<T>(stages, std::forward<Args>(args)...);
    }

    template <typename T>
    void removeSystem()
    {
        systemManager.removeSystem<T>();
    }

    template <typename T>
    T *getSystem()
    {
        return systemManager.getSystem<T>();
    }

private:
    EventBus eventBus{};
    Registry registry{};
    SystemManager systemManager{*this};
};
