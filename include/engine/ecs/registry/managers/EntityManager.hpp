#pragma once
#include <cstdint>
#include <vector>

#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/ecs/registry/entities/EntitySlot.hpp>

class EntityManager
{
public:
    EntityManager() = default;

    EntityId create();
    void destroy(EntityId entity);
    bool valid(EntityId entity) const;

private:
    std::vector<EntitySlot> slots;
    std::vector<uint32_t> freeIds;
};
