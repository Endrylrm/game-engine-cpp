#pragma once
#include <stdexcept>
#include <vector>

#include "engine/ecs/registry/entities/EntityId.hpp"

template <typename T>
class ComponentSparseSet
{
public:
    ComponentSparseSet(size_t capacity = 1024) : sparse(capacity, INVALID) {}

    template <typename... Args>
    T &emplace(EntityId entity, Args &&...args)
    {
        if (contains(entity))
            return dense[sparse[entity.index]];

        ensure_sparse_size(entity);

        sparse[entity.index] = dense.size();

        dense_entities.push_back(entity);
        dense.emplace_back(std::forward<Args>(args)...);

        return dense.back();
    }

    bool contains(EntityId entity) const
    {
        return entity.index < sparse.size() && sparse[entity.index] != INVALID;
    }

    void erase(EntityId entity)
    {
        if (!contains(entity))
            return;

        size_t index = sparse[entity.index];
        size_t last_dense_index = dense.size() - 1;
        EntityId last_entity = dense_entities[last_dense_index];

        dense[index] = std::move(dense[last_dense_index]);
        dense_entities[index] = last_entity;
        sparse[last_entity.index] = index;

        dense.pop_back();
        dense_entities.pop_back();
        sparse[entity.index] = INVALID;
    }

    T *find(EntityId entity)
    {
        return contains(entity) ? &dense[sparse[entity.index]] : nullptr;
    }

    const T *find(EntityId entity) const
    {
        return contains(entity) ? &dense[sparse[entity.index]] : nullptr;
    }

    T &at(EntityId entity)
    {
        if (!contains(entity))
            throw std::out_of_range("Entity don't exist in SparseSet!");

        return dense[sparse[entity.index]];
    }

    const T &at(EntityId entity) const
    {
        if (!contains(entity))
            throw std::out_of_range("Entity don't exist in SparseSet!");

        return dense[sparse[entity.index]];
    }

    T &at(size_t index)
    {
        return dense[index];
    }

    const T &at(size_t index) const
    {
        return dense[index];
    }

    EntityId entity_at(size_t index) const
    {
        return dense_entities[index];
    }

    const std::vector<T> &components() const
    {
        return dense;
    }

    const std::vector<EntityId> &entities() const
    {
        return dense_entities;
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
        dense_entities.clear();
        std::fill(sparse.begin(), sparse.end(), INVALID);
    }

    T &operator[](EntityId entity)
    {
        assert(contains(entity));
        return dense[sparse[entity.index]];
    }

    const T &operator[](EntityId entity) const
    {
        assert(contains(entity));
        return dense[sparse[entity.index]];
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
    void ensure_sparse_size(EntityId entity)
    {
        size_t index = static_cast<size_t>(entity.index);

        if (index >= sparse.size())
        {
            sparse.resize(index + 1);
        }
    }

    std::vector<size_t> sparse;
    std::vector<EntityId> dense_entities;
    std::vector<T> dense;

    static constexpr size_t INVALID = std::numeric_limits<size_t>::max();
};