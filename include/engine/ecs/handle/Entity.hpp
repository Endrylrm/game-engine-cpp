#pragma once
#include "engine/ecs/registry/entities/EntityId.hpp"
#include "engine/ecs/world/World.hpp"

class Entity
{
public:
    Entity() = default;
    Entity(EntityId id, World *world) : id(id), world(world) {}
    ~Entity() = default;

    template <typename T, typename... Args>
    T &add_component(Args &&...args)
    {
        return world->add_component<T>(id, std::forward<Args>(args)...);
    }

    template <typename T>
    T &get_component()
    {
        return world->get_component<T>(id);
    }

    template <typename T>
    T &get_or_add_component()
    {
        return world->get_or_add_component<T>(id);
    }

    template <typename T>
    T *try_get_component()
    {
        return world->try_get_component<T>(id);
    }

    template <typename T>
    void remove_component()
    {
        world->remove_component<T>(id);
    }

    template <typename T>
    bool has_component()
    {
        return world->has_component<T>(id);
    }

    void mark_for_destruction()
    {
        world->destroy_entity(id);
    }

    bool is_valid() const
    {
        return world != nullptr && world->is_valid_entity(id);
    }

    EntityId get_id()
    {
        return id;
    }

private:
    World *world;
    EntityId id{};
};
