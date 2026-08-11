#pragma once
#include <stdexcept>
#include <vector>

#include <engine/ecs/registry/entities/EntityId.hpp>

template <typename T>
class ComponentSparseSet
{
public:
    ComponentSparseSet(size_t capacity = 1024) : sparse(capacity, INVALID) {}

    template <typename... Args>
    T &emplace(EntityId entity, Args &&...args)
    {
        if (contains(entity))
            return dense[sparse[entity.id]];

        ensureSparseSize(entity);

        sparse[entity.id] = dense.size();

        denseEntities.push_back(entity);
        dense.emplace_back(std::forward<Args>(args)...);

        return dense.back();
    }

    bool contains(EntityId entity) const
    {
        return entity.id < sparse.size() && sparse[entity.id] != INVALID;
    }

    void erase(EntityId entity)
    {
        if (!contains(entity))
            return;

        size_t index = sparse[entity.id];
        size_t lastDenseIndex = dense.size() - 1;
        EntityId lastEntity = denseEntities[lastDenseIndex];

        dense[index] = std::move(dense[lastDenseIndex]);
        denseEntities[index] = lastEntity;
        sparse[lastEntity.id] = index;

        dense.pop_back();
        denseEntities.pop_back();
        sparse[entity.id] = INVALID;
    }

    T *find(EntityId entity)
    {
        return contains(entity) ? &dense[sparse[entity.id]] : nullptr;
    }

    const T *find(EntityId entity) const
    {
        return contains(entity) ? &dense[sparse[entity.id]] : nullptr;
    }

    T &at(EntityId entity)
    {
        if (!contains(entity))
            throw std::out_of_range("Entity don't exist in SparseSet!");

        return dense[sparse[entity.id]];
    }

    const T &at(EntityId entity) const
    {
        if (!contains(entity))
            throw std::out_of_range("Entity don't exist in SparseSet!");

        return dense[sparse[entity.id]];
    }

    T &at(size_t index)
    {
        return dense[index];
    }

    const T &at(size_t index) const
    {
        return dense[index];
    }

    EntityId entityAt(size_t index) const
    {
        return denseEntities[index];
    }

    const std::vector<T> &components() const
    {
        return dense;
    }

    const std::vector<EntityId> &entities() const
    {
        return denseEntities;
    }

    size_t size() const
    {
        return dense.size();
    }

    bool empty() const
    {
        return dense.empty();
    }

    void clear()
    {
        dense.clear();
        denseEntities.clear();
        std::fill(sparse.begin(), sparse.end(), INVALID);
    }

    T &operator[](EntityId entity)
    {
        assert(contains(entity));
        return dense[sparse[entity.id]];
    }

    const T &operator[](EntityId entity) const
    {
        assert(contains(entity));
        return dense[sparse[entity.id]];
    }

    auto begin()
    {
        return dense.begin();
    }

    auto end()
    {
        return dense.end();
    }

    auto begin() const
    {
        return dense.begin();
    }

    auto end() const
    {
        return dense.end();
    }

private:
    void ensureSparseSize(EntityId entity)
    {
        size_t index = static_cast<size_t>(entity.id);

        if (index >= sparse.size())
        {
            sparse.resize(index + 1);
        }
    }

    std::vector<size_t> sparse;
    std::vector<EntityId> denseEntities;
    std::vector<T> dense;

    static constexpr size_t INVALID = std::numeric_limits<size_t>::max();
};