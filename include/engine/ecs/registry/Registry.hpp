#pragma once
#include <vector>

#include "engine/ecs/registry/entities/EntityId.hpp"
#include "engine/ecs/registry/managers/ComponentManager.hpp"
#include "engine/ecs/registry/managers/EntityManager.hpp"
#include "engine/ecs/registry/views/View.hpp"

class Registry
{
public:
    EntityId create_entity()
    {
        return entity_manager.create();
    }

    void destroy_entity(EntityId entity)
    {
        if (!entity_manager.valid(entity))
            return;

        destroy_queue.push_back(entity);
    }

    bool is_valid_entity(EntityId entity) const
    {
        return entity_manager.valid(entity);
    }

    void process_destroy_queue()
    {
        for (auto entity : destroy_queue)
        {
            if (entity_manager.valid(entity))
                destroy_immediate(entity);
        }

        destroy_queue.clear();
    }

    template <typename T, typename... Args>
    T &add_component(EntityId entity, Args &&...args)
    {
        return component_manager.add<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T &add_component(EntityId entity, T &&value)
    {
        return component_manager.add<T>(entity, std::move(value));
    }

    template <typename T>
    T &get_component(EntityId entity)
    {
        return component_manager.get<T>(entity);
    }

    template <typename T>
    T &get_or_add_component(EntityId entity)
    {
        return component_manager.get_or_add<T>(entity);
    }

    template <typename T>
    T *try_get_component(EntityId entity)
    {
        return component_manager.try_get<T>(entity);
    }

    template <typename T>
    bool has_component(EntityId entity)
    {
        return component_manager.has<T>(entity);
    }

    template <typename T>
    void remove_component(EntityId entity)
    {
        component_manager.remove<T>(entity);
    }

    void remove_all_components(EntityId entity)
    {
        component_manager.remove_all(entity);
    }

    template <typename... Components>
    View<Components...> view()
    {
        return View<Components...>(component_manager.get_storage_ref<Components>()...);
    }

private:
    void destroy_immediate(EntityId entity)
    {
        component_manager.remove_all(entity);
        entity_manager.destroy(entity);
    }

    EntityManager entity_manager{};
    ComponentManager component_manager{};
    std::vector<EntityId> destroy_queue{};
};
