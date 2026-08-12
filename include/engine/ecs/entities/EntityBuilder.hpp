#pragma once

#include <engine/ecs/handle/Entity.hpp>
#include <engine/scenes/Scene.hpp>

class EntityBuilder
{
public:
    EntityBuilder(Scene &scene) : entity(scene.createEntity()) {}

    template <typename T, typename... Args>
    EntityBuilder &addComponent(Args &&...args)
    {
        entity.addComponent<T>(std::forward<Args>(args)...);
        return *this;
    }

    template <typename T>
    EntityBuilder &addComponent(T &&value)
    {
        entity.addComponent<T>(std::move(value));
        return *this;
    }

    Entity build()
    {
        return std::move(entity);
    }

private:
    Entity entity;
};