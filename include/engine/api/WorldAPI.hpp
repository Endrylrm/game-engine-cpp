#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/core/helpers/Flags.hpp"
#include "engine/ecs/handle/Entity.hpp"
#include "engine/ecs/registry/entities/EntityId.hpp"
#include "engine/ecs/registry/systems/SystemStage.hpp"
#include "engine/ecs/registry/views/View.hpp"
#include "engine/ecs/systems/System.hpp"
#include "engine/ecs/world/World.hpp"

class WorldAPI : public ManagerAPI<World>
{
public:
    static Entity create_entity()
    {
        return get_manager().create_entity();
    }

    static Entity get_entity(EntityId id)
    {
        return get_manager().get_entity(id);
    }

    static void destroy_entity(EntityId entity)
    {
        get_manager().destroy_entity(entity);
    }

    template <typename T, typename... Args>
    static T &add_component(EntityId entity, Args &&...args)
    {
        return get_manager().add_component<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    static T &add_component(EntityId entity, T &&value)
    {
        return get_manager().add_component<T>(entity, std::move(value));
    }

    template <typename T>
    static T &get_component(EntityId entity)
    {
        return get_manager().get_component<T>(entity);
    }

    template <typename T>
    static T &get_or_add_component(EntityId entity)
    {
        return get_manager().get_or_add_component<T>(entity);
    }

    template <typename T>
    static T *try_get_component(EntityId entity)
    {
        return get_manager().try_get_component<T>(entity);
    }

    template <typename T>
    static bool has_component(EntityId entity)
    {
        return get_manager().has_component<T>(entity);
    }

    template <typename T>
    static void remove_component(EntityId entity)
    {
        get_manager().remove_component<T>(entity);
    }

    static void remove_all_components(EntityId entity)
    {
        get_manager().remove_all_components(entity);
    }

    template <typename... Components>
    static View<Components...> view()
    {
        return get_manager().view<Components...>();
    }

    template <std::derived_from<System> T, typename... Args>
    static T &add_system(Flags<SystemStage> stages, Args &&...args)
    {
        return get_manager().add_system<T>(stages, std::forward<Args>(args)...);
    }

    template <typename T>
    static void remove_system()
    {
        get_manager().remove_system<T>();
    }

    template <typename T>
    static T *get_system()
    {
        return get_manager().get_system<T>();
    }
};
