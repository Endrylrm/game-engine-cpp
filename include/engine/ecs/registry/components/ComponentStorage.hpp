#pragma once
#include <engine/ecs/registry/components/ComponentSparseSet.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>

class BaseComponentStorage
{
public:
    virtual ~BaseComponentStorage() = default;
    virtual void erase(EntityId entity) = 0;
};

template <typename ComponentType>
class ComponentStorage : public BaseComponentStorage
{
public:
    template <typename... Args>
    ComponentType &emplace(EntityId entity, Args &&...args)
    {
        return sparse.emplace(entity, std::forward<Args>(args)...);
    }

    bool contains(EntityId entity) const
    {
        return sparse.contains(entity);
    }

    void erase(EntityId entity) override
    {
        sparse.erase(entity);
    }

    ComponentType *find(EntityId entity)
    {
        return contains(entity) ? sparse.find(entity) : nullptr;
    }

    const ComponentType *find(EntityId entity) const
    {
        return contains(entity) ? sparse.find(entity) : nullptr;
    }

    ComponentType &at(EntityId entity)
    {
        return sparse.at(entity);
    }

    const ComponentType &at(EntityId entity) const
    {
        return sparse.at(entity);
    }

    ComponentType &at(size_t index)
    {
        return sparse.at(index);
    }

    const ComponentType &at(size_t index) const
    {
        return sparse.at(index);
    }

    EntityId entityAt(size_t index) const
    {
        return sparse.entityAt(index);
    }

    const std::vector<ComponentType> &components() const
    {
        return sparse.components();
    }

    const std::vector<EntityId> &entities() const
    {
        return sparse.entities();
    }

    size_t size() const
    {
        return sparse.size();
    }

    bool empty() const
    {
        return sparse.empty();
    }

    void clear()
    {
        sparse.clear();
    }

    ComponentType &operator[](EntityId entity)
    {
        return sparse[entity];
    }

    const ComponentType &operator[](EntityId entity) const
    {
        return sparse[entity];
    }

    auto begin()
    {
        return sparse.begin();
    }

    auto end()
    {
        return sparse.end();
    }

    auto begin() const
    {
        return sparse.begin();
    }

    auto end() const
    {
        return sparse.end();
    }

private:
    ComponentSparseSet<ComponentType> sparse;
};