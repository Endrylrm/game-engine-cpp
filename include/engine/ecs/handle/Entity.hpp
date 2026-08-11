#pragma once
#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/scenes/Scene.hpp>

class Entity
{
public:
    Entity() = default;
    Entity(EntityId id, Scene *scene) : id(id), scene(scene) {}
    ~Entity() = default;

    template <typename T, typename... Args>
    T &addComponent(Args &&...args)
    {
        return scene->getRegistry().addComponent<T>(id, std::forward<Args>(args)...);
    }

    template <typename T>
    T &getComponent()
    {
        return scene->getRegistry().getComponent<T>(id);
    }

    template <typename T>
    T &getOrAddComponent()
    {
        return scene->getRegistry().getOrAddComponent<T>(id);
    }

    template <typename T>
    T *tryGetComponent()
    {
        return scene->getRegistry().tryGetComponent<T>(id);
    }

    template <typename T>
    void removeComponent()
    {
        scene->getRegistry().removeComponent<T>(id);
    }

    template <typename T>
    bool hasComponent()
    {
        return scene->getRegistry().hasComponent<T>(id);
    }

    void markForDestruction()
    {
        scene->queueDestroyEntity(id);
    }

    Scene *scene{};
    EntityId id{};
};
