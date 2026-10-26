#include "engine/ecs/registry/managers/EntityManager.hpp"

#include "engine/core/log/Log.hpp"

EntityId EntityManager::create()
{
    uint32_t index;

    if (!free_ids.empty())
    {
        index = free_ids.back();
        free_ids.pop_back();

        auto &slot = slots[index];
        slot.alive = true;
    }
    else
    {
        index = slots.size();
        slots.push_back({0, true});
    }

    LOG_DEBUG("Entity id: '{}', generation: {} created.", index, slots[index].generation);
    return {index, slots[index].generation};
}

void EntityManager::destroy(EntityId entity)
{
    if (!valid(entity))
        return;

    auto &slot = slots[entity.index];
    slot.alive = false;
    slot.generation++;

    free_ids.push_back(entity.index);
    LOG_DEBUG("Entity destroyed: {}, {}.", entity.index, entity.generation);
}

bool EntityManager::valid(EntityId entity) const
{
    if (entity.index >= slots.size())
        return false;

    const auto &slot = slots[entity.index];

    return slot.alive && slot.generation == entity.generation;
}
