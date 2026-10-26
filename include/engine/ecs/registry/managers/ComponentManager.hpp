#pragma once
#include <memory>

#include "engine/core/log/Log.hpp"
#include "engine/core/log/TypeName.hpp"
#include "engine/ecs/registry/components/ComponentRegistry.hpp"
#include "engine/ecs/registry/components/ComponentStorage.hpp"
#include "engine/ecs/registry/entities/EntityId.hpp"

class ComponentManager
{
public:
    template <typename T, typename... Args>
    T &add(EntityId entity, Args &&...args)
    {
        T &component = get_storage<T>().emplace(entity, std::forward<Args>(args)...);
        LOG_DEBUG("Added Component {} to Entity {}", get_type_name<T>(), entity.index);
        return component;
    }

    template <typename T>
    T &get(EntityId entity)
    {
        T &component = get_storage<T>().at(entity);
        LOG_DEBUG("got Component {} to Entity {}", get_type_name<T>(), entity.index);
        return component;
    }

    template <typename T, typename... Args>
    T &get_or_add(EntityId entity, Args &&...args)
    {
        bool has_component = get_storage<T>().contains(entity);

        if (has_component)
        {
            T &component = get<T>(entity);
            LOG_DEBUG("got Component {} from Entity {}", get_type_name<T>(), entity.index);
            return component;
        }

        T &component = add<T>(entity, std::forward<Args>(args)...);
        LOG_DEBUG("added Component {} to Entity {}", get_type_name<T>(), entity.index);
        return component;
    }

    template <typename T>
    T *try_get(EntityId entity)
    {
        T *component = get_storage<T>().find(entity);
        if (component)
            LOG_DEBUG("got Component {} from Entity {}", get_type_name<T>(), entity.index);
        else
            LOG_DEBUG("has no Component {} in Entity {}", get_type_name<T>(), entity.index);
        return component;
    }

    template <typename T>
    bool has(EntityId entity)
    {
        bool has_component = get_storage<T>().contains(entity);
        LOG_DEBUG("Entity {} has component: {}", entity.index, get_type_name<T>());
        return has_component;
    }

    template <typename T>
    void remove(EntityId entity)
    {
        get_storage<T>().erase(entity);
        LOG_DEBUG("Erased Component {} from Entity {}", get_type_name<T>(), entity.index);
    }

    void remove_all(EntityId entity)
    {
        for (auto &storage : storages)
        {
            storage->erase(entity);
        }
        LOG_DEBUG("Erased all Components from Entity {}", entity.index);
    }

    template <typename T>
    ComponentStorage<T> &get_storage_ref()
    {
        return get_storage<T>();
    }

    template <typename T>
    const ComponentStorage<T> &get_storage_ref() const
    {
        return const_cast<ComponentManager *>(this)->get_storage<T>();
    }

private:
    template <typename T>
    ComponentStorage<T> &get_storage()
    {
        ComponentId id = ComponentRegistry::get_type_id<T>();

        if (id >= storages.size())
            storages.resize(id + 1);

        if (!storages[id])
            storages[id] = std::make_unique<ComponentStorage<T>>();

        return *static_cast<ComponentStorage<T> *>(storages[id].get());
    }

    std::vector<std::unique_ptr<BaseComponentStorage>> storages;
};
