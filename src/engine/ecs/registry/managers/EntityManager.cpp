#include "engine/ecs/registry/managers/EntityManager.hpp"

EntityId EntityManager::create()
{
    uint32_t index;

    if (!freeIds.empty())
    {
        index = freeIds.back();
        freeIds.pop_back();

        auto &slot = slots[index];
        slot.alive = true;
    }
    else
    {
        index = slots.size();
        slots.push_back({0, true});
    }

    return {index, slots[index].generation};
}

void EntityManager::destroy(EntityId entity)
{
    if (!valid(entity))
        return;

    auto &slot = slots[entity.id];
    slot.alive = false;
    slot.generation++;

    freeIds.push_back(entity.id);
}

bool EntityManager::valid(EntityId entity) const
{
    if (entity.id >= slots.size())
        return false;

    const auto &slot = slots[entity.id];

    return slot.alive && slot.generation == entity.generation;
}
