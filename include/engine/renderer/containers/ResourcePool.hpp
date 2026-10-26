#pragma once
#include <cstdint>
#include <vector>

#include "engine/core/handle/TypedHandle.hpp"
#include "engine/core/log/Log.hpp"

#include "ResourceSlot.hpp"

template <typename NativeResource, typename Tag>
class ResourcePool
{
public:
    using Handle = TypedHandle<Tag>;

    ResourcePool() = default;

    Handle insert(NativeResource resource)
    {
        uint32_t index;

        if (!free_ids.empty())
        {
            index = free_ids.back();
            free_ids.pop_back();
        }
        else
        {
            index = slots.size();
            slots.emplace_back();
        }

        auto &slot = slots[index];
        slot.resource.emplace(std::move(resource));
        slot.alive = true;
        cur_size++;

        LOG_DEBUG("Resource id: '{}', generation: {} created.", index, slots[index].generation);
        return Handle{.index = index, .generation = slots[index].generation};
    }

    void destroy(Handle handle)
    {
        if (!valid(handle))
            return;

        auto &slot = slots[handle.index];
        slot.resource.reset();
        slot.alive = false;
        slot.generation++;

        free_ids.push_back(handle.index);
        cur_size--;
        LOG_DEBUG("Resoruce destroyed: {}, {}.", handle.index, handle.generation);
    }

    bool valid(Handle handle) const
    {
        if (handle.index >= slots.size())
            return false;

        const auto &slot = slots[handle.index];

        return slot.alive && slot.generation == handle.generation;
    }

    NativeResource *get(Handle handle)
    {
        if (!valid(handle))
            return nullptr;

        return &*slots[handle.index].resource;
    }

    const NativeResource *get(Handle handle) const
    {
        if (!valid(handle))
            return nullptr;

        return &*slots[handle.index].resource;
    }

    size_t size() const noexcept
    {
        return cur_size;
    }

    bool empty() const noexcept
    {
        return cur_size == 0;
    }

private:
    std::vector<ResourceSlot<NativeResource>> slots;
    std::vector<uint32_t> free_ids;
    size_t cur_size = 0;
};
