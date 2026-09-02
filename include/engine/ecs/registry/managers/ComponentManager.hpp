#pragma once
#include <memory>

#include <engine/core/log/Log.hpp>
#include <engine/core/log/TypeName.hpp>
#include <engine/ecs/registry/components/ComponentRegistry.hpp>
#include <engine/ecs/registry/components/ComponentStorage.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>

class ComponentManager
{
public:
    template <typename T, typename... Args>
    T &add(EntityId entity, Args &&...args)
    {
        T &component = getStorage<T>().emplace(entity, std::forward<Args>(args)...);
        LOG_DEBUG("Added Component {} to Entity {}", getTypeName<T>(), entity.id);
        return component;
    }

    template <typename T>
    T &get(EntityId entity)
    {
        T &component = getStorage<T>().at(entity);
        LOG_DEBUG("got Component {} to Entity {}", getTypeName<T>(), entity.id);
        return component;
    }

    template <typename T, typename... Args>
    T &getOrAdd(EntityId entity, Args &&...args)
    {
        bool hasComponent = getStorage<T>().contains(entity);

        if (hasComponent)
        {
            T &component = get<T>(entity);
            LOG_DEBUG("got Component {} from Entity {}", getTypeName<T>(), entity.id);
            return component;
        }

        T &component = add<T>(entity, std::forward<Args>(args)...);
        LOG_DEBUG("added Component {} to Entity {}", getTypeName<T>(), entity.id);
        return component;
    }

    template <typename T>
    T *tryGet(EntityId entity)
    {
        T *component = getStorage<T>().find(entity);
        if (component)
            LOG_DEBUG("got Component {} from Entity {}", getTypeName<T>(), entity.id);
        else
            LOG_DEBUG("has no Component {} in Entity {}", getTypeName<T>(), entity.id);
        return component;
    }

    template <typename T>
    bool has(EntityId entity)
    {
        bool hasComponent = getStorage<T>().contains(entity);
        LOG_DEBUG("Entity {} has component: {}", entity.id, getTypeName<T>());
        return hasComponent;
    }

    template <typename T>
    void remove(EntityId entity)
    {
        getStorage<T>().erase(entity);
        LOG_DEBUG("Erased Component {} from Entity {}", getTypeName<T>(), entity.id);
    }

    void removeAll(EntityId entity)
    {
        for (auto &storage : storages)
        {
            storage->erase(entity);
        }
        LOG_DEBUG("Erased all Components from Entity {}", entity.id);
    }

    template <typename T>
    ComponentStorage<T> &getStorageRef()
    {
        return getStorage<T>();
    }

    template <typename T>
    const ComponentStorage<T> &getStorageRef() const
    {
        return const_cast<ComponentManager *>(this)->getStorage<T>();
    }

private:
    template <typename T>
    ComponentStorage<T> &getStorage()
    {
        ComponentId id = ComponentRegistry::getTypeId<T>();

        if (id >= storages.size())
            storages.resize(id + 1);

        if (!storages[id])
            storages[id] = std::make_unique<ComponentStorage<T>>();

        return *static_cast<ComponentStorage<T> *>(storages[id].get());
    }

    std::vector<std::unique_ptr<BaseComponentStorage>> storages;
};
