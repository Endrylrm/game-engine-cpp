#pragma once
#include <engine/api/ManagerAPI.hpp>
#include <engine/core/helpers/Flags.hpp>
#include <engine/ecs/handle/Entity.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/registry/views/View.hpp>
#include <engine/ecs/systems/System.hpp>
#include <engine/ecs/world/World.hpp>

class WorldAPI : public ManagerAPI<World>
{
public:
    static Entity createEntity()
    {
        return getManager().createEntity();
    }

    static void destroyEntity(EntityId entity)
    {
        getManager().destroyEntity(entity);
    }

    template <typename T, typename... Args>
    static T &addComponent(EntityId entity, Args &&...args)
    {
        return getManager().addComponent<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    static T &addComponent(EntityId entity, T &&value)
    {
        return getManager().addComponent<T>(entity, std::move(value));
    }

    template <typename T>
    static T &getComponent(EntityId entity)
    {
        return getManager().getComponent<T>(entity);
    }

    template <typename T>
    static T &getOrAddComponent(EntityId entity)
    {
        return getManager().getOrAddComponent<T>(entity);
    }

    template <typename T>
    static T *tryGetComponent(EntityId entity)
    {
        return getManager().tryGetComponent<T>(entity);
    }

    template <typename T>
    static bool hasComponent(EntityId entity)
    {
        return getManager().hasComponent<T>(entity);
    }

    template <typename T>
    static void removeComponent(EntityId entity)
    {
        getManager().removeComponent<T>(entity);
    }

    static void removeAllComponents(EntityId entity)
    {
        getManager().removeAllComponents(entity);
    }

    template <typename... Components>
    static View<Components...> view()
    {
        return getManager().view<Components...>();
    }

    template <std::derived_from<System> T, typename... Args>
    static T &addSystem(Flags<SystemStage> stages, Args &&...args)
    {
        return getManager().addSystem<T>(stages, std::forward<Args>(args)...);
    }

    template <typename T>
    static void removeSystem()
    {
        getManager().removeSystem<T>();
    }

    template <typename T>
    static T *getSystem()
    {
        return getManager().getSystem<T>();
    }
};
