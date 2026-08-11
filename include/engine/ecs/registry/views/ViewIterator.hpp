#pragma once
#include <tuple>
#include <vector>

#include <engine/ecs/registry/components/ComponentStorage.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>

template <typename... Components>
struct ViewIterator
{
    using EntityIt = std::vector<EntityId>::const_iterator;

    ViewIterator(EntityIt it, EntityIt end, std::tuple<ComponentStorage<Components> &...> &storages)
        : iter(it), end(end), storages(storages)
    {
        skipInvalid();
    }

    bool operator==(const ViewIterator &other) const
    {
        return iter == other.iter;
    }

    bool operator!=(const ViewIterator &other) const
    {
        return !(*this == other);
    }

    ViewIterator &operator++()
    {
        ++iter;
        skipInvalid();
        return *this;
    }

    std::tuple<Components &...> operator*()
    {
        EntityId entity = *iter;
        return std::tuple<Components &...>(
            std::get<ComponentStorage<Components> &>(storages).at(entity)...
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

    EntityIt iter, end;
    std::tuple<ComponentStorage<Components> &...> &storages;
};
