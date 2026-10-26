#pragma once
#include "engine/ecs/handle/Entity.hpp"
#include "engine/scenes/Scene.hpp"

class EntityBuilder
{
public:
    EntityBuilder(Scene &scene) : entity(scene.create_entity()) {}

    template <typename T, typename... Args>
    EntityBuilder &add_component(Args &&...args)
    {
        entity.add_component<T>(std::forward<Args>(args)...);
        return *this;
    }

    template <typename T>
    EntityBuilder &add_component(T &&value)
    {
        entity.add_component<T>(std::move(value));
        return *this;
    }

    Entity build()
    {
        return std::move(entity);
    }

private:
    Entity entity;
};