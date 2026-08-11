#pragma once
#include <vector>

#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/ecs/registry/managers/ComponentManager.hpp>
#include <engine/ecs/registry/managers/EntityManager.hpp>
#include <engine/ecs/registry/views/View.hpp>

class Registry
{
public:
    EntityId createEntity()
    {
        return entityManager.create();
    }

    void destroyEntity(EntityId entity)
    {
        destroyQueue.push_back(entity);
    }

    bool validEntity(EntityId entity) const
    {
        return entityManager.valid(entity);
    }

    void processDestroyQueue()
    {
        for (auto entity : destroyQueue)
        {
            if (entityManager.valid(entity))
                destroyImmediate(entity);
        }

        destroyQueue.clear();
    }

    template <typename T, typename... Args>
    T &addComponent(EntityId entity, Args &&...args)
    {
        return componentManager.add<T>(entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T &addComponent(EntityId entity, T &&value)
    {
        return componentManager.add<T>(entity, std::move(value));
    }

    template <typename T>
    T &getComponent(EntityId entity)
    {
        return componentManager.get<T>(entity);
    }

    template <typename T>
    T &getOrAddComponent(EntityId entity)
    {
        return componentManager.getOrAdd<T>(entity);
    }

    template <typename T>
    T *tryGetComponent(EntityId entity)
    {
        return componentManager.tryGet<T>(entity);
    }

    template <typename T>
    bool hasComponent(EntityId entity)
    {
        return componentManager.has<T>(entity);
    }

    template <typename T>
    void removeComponent(EntityId entity)
    {
        componentManager.remove<T>(entity);
    }

    void removeAllComponents(EntityId entity)
    {
        componentManager.removeAll(entity);
    }

    template <typename... Components>
    View<Components...> view()
    {
        return View<Components...>(componentManager.getStorageRef<Components>()...);
    }

private:
    void destroyImmediate(EntityId entity)
    {
        componentManager.removeAll(entity);
        entityManager.destroy(entity);
    }

    EntityManager entityManager{};
    ComponentManager componentManager{};
    std::vector<EntityId> destroyQueue{};
};
