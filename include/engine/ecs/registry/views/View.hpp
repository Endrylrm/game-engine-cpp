#pragma once
#include <tuple>
#include <vector>

#include <engine/ecs/registry/components/ComponentStorage.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>

#include "ViewEntity.hpp"
#include "ViewEntityIterator.hpp"
#include "ViewIterator.hpp"

template <typename... Components>
class View
{
public:
    explicit View(ComponentStorage<Components> &...storages) : storages(storages...)
    {
        createSnapshot();
    }

    ViewEntity<Components...> withEntities()
    {
        return ViewEntity<Components...>(*this);
    }

    ViewIterator<Components...> begin()
    {
        return ViewIterator<Components...>(snapshot.begin(), snapshot.end(), storages);
    }

    ViewIterator<Components...> end()
    {
        return ViewIterator<Components...>(snapshot.end(), snapshot.end(), storages);
    }

    ViewEntityIterator<Components...> beginEntity()
    {
        return ViewEntityIterator<Components...>(snapshot.begin(), snapshot.end(), storages);
    }

    ViewEntityIterator<Components...> endEntity()
    {
        return ViewEntityIterator<Components...>(snapshot.end(), snapshot.end(), storages);
    }

private:
    void createSnapshot()
    {
        const auto &pivot = pivotEntities();
        snapshot = pivot;
    }

    const std::vector<EntityId> &pivotEntities() const
    {
        const std::vector<EntityId> *smallest = nullptr;
        auto checkStorageSize = [&](const auto &storage)
        {
            if (!smallest || storage.entities().size() < smallest->size())
                smallest = &storage.entities();
        };
        std::apply([&](auto &...storage) { (checkStorageSize(storage), ...); }, storages);
        return *smallest;
    }

    std::tuple<ComponentStorage<Components> &...> storages;
    std::vector<EntityId> snapshot;
};
