#pragma once
#include <tuple>
#include <vector>

#include <engine/ecs/registry/components/ComponentStorage.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>

template <typename... Components>
struct ViewEntityIterator
{
    using EntityIt = std::vector<EntityId>::const_iterator;

    ViewEntityIterator(
        EntityIt it, EntityIt end, std::tuple<ComponentStorage<Components> &...> &storages
    )
        : iter(it), end(end), storages(storages)
    {
        skipInvalid();
    }

    bool operator==(const ViewEntityIterator &other) const
    {
        return iter == other.iter;
    }

    bool operator!=(const ViewEntityIterator &other) const
    {
        return !(*this == other);
    }

    ViewEntityIterator &operator++()
    {
        ++iter;
        skipInvalid();
        return *this;
    }

    auto operator*()
    {
        EntityId entity = *iter;

        return std::tuple_cat(
            std::tuple<EntityId>{entity},
            std::tuple<Components &...>(
                std::get<ComponentStorage<Components> &>(storages).at(entity)...
            )
        );
    }

private:
    void skipInvalid()
    {
        while (iter != end && !allContain(*iter))
            ++iter;
    }

    bool allContain(EntityId entity) const
    {
        return (std::get<ComponentStorage<Components> &>(storages).contains(entity) && ...);
    }

    EntityIt iter;
    EntityIt end;
    std::tuple<ComponentStorage<Components> &...> &storages;
};