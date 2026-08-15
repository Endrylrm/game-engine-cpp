#pragma once
#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/ecs/world/World.hpp>

class Entity
{
public:
    Entity() = default;
    Entity(EntityId id, World *world) : id(id), world(world) {}
    ~Entity() = default;

    template <typename T, typename... Args>
    T &addComponent(Args &&...args)
    {
        return world->addComponent<T>(id, std::forward<Args>(args)...);
    }

    template <typename T>
    T &getComponent()
    {
        return world->getComponent<T>(id);
    }

    template <typename T>
    T &getOrAddComponent()
    {
        return world->getOrAddComponent<T>(id);
    }

    template <typename T>
    T *tryGetComponent()
    {
        return world->tryGetComponent<T>(id);
    }

    template <typename T>
    void removeComponent()
    {
        world->removeComponent<T>(id);
    }

    template <typename T>
    bool hasComponent()
    {
        return world->hasComponent<T>(id);
    }

    void markForDestruction()
    {
        world->destroyEntity(id);
    }

    bool isValid() const
    {
        return world != nullptr && world->isValidEntity(id);
    }

    EntityId getId()
    {
        return id;
    }

private:
    World *world;
    EntityId id{};
};
