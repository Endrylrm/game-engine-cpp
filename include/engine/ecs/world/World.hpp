#pragma once
#include "engine/core/events/EventBus.hpp"
#include "engine/ecs/registry/Registry.hpp"
#include "engine/ecs/registry/entities/EntityId.hpp"
#include "engine/ecs/registry/managers/SystemManager.hpp"
#include "engine/ecs/registry/systems/SystemStage.hpp"
#include "engine/ecs/registry/views/View.hpp"
#include "engine/ecs/systems/System.hpp"
#include "engine/renderer/Renderer.hpp"

class Entity;

class World
{
public:
    void init();
    void events();
    void physics(float fixed_delta_time);
    void pre_update();
    void update(float delta_time);
    void post_update();
    void render(Renderer &renderer);
    void process_lifecycle();
    void unload();

    Entity create_entity();
    Entity get_entity(EntityId id);
    void destroy_entity(EntityId entity);
    bool is_valid_entity(EntityId entity) const;

    template <typename T, typename... Args>
    T &add_component(EntityId entity, Args &&...args)
    {
        return registry.add_component<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T &add_component(EntityId entity, T &&value)
    {
        return registry.add_component<T>(entity, std::move(value));
    }

    template <typename T>
    T &get_component(EntityId entity)
    {
        return registry.get_component<T>(entity);
    }

    template <typename T>
    T &get_or_add_component(EntityId entity)
    {
        return registry.get_or_add_component<T>(entity);
    }

    template <typename T>
    T *try_get_component(EntityId entity)
    {
        return registry.try_get_component<T>(entity);
    }

    template <typename T>
    bool has_component(EntityId entity)
    {
        return registry.has_component<T>(entity);
    }

    template <typename T>
    void remove_component(EntityId entity)
    {
        registry.remove_component<T>(entity);
    }

    void remove_all_components(EntityId entity);

    template <typename... Components>
    View<Components...> view()
    {
        return registry.view<Components...>();
    }

    template <std::derived_from<System> T, typename... Args>
    T &add_system(Flags<SystemStage> stages, Args &&...args)
    {
        return system_manager.add_system<T>(stages, std::forward<Args>(args)...);
    }

    template <typename T>
    void remove_system()
    {
        system_manager.remove_system<T>();
    }

    template <typename T>
    T *get_system()
    {
        return system_manager.get_system<T>();
    }

private:
    EventBus event_bus{};
    Registry registry{};
    SystemManager system_manager{*this};
};
