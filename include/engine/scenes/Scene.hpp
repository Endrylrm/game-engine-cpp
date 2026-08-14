#pragma once
#include <engine/ecs/world/World.hpp>

#include "SceneId.hpp"

class Entity;

class Scene
{
public:
    Scene(SceneId id, World &world) : id(id), world(world) {}
    ~Scene() = default;

    void unload();

    Entity createEntity();

    SceneId getId() const
    {
        return id;
    }

private:
    World &world;
    SceneId id;
};
