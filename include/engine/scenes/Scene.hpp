#pragma once
#include <functional>

#include <engine/ecs/world/World.hpp>

#include "SceneId.hpp"

class Entity;

class Scene
{
public:
    using SceneCallback = std::function<void(Scene &)>;

    Scene(SceneId id, World &world) : id(id), world(world) {}
    ~Scene() = default;

    void load();
    void unload();

    Entity createEntity();

    SceneId getId() const;

    void setOnLoad(SceneCallback callback);
    void setOnUnload(SceneCallback callback);

    World &getWorld();

private:
    World &world;
    SceneId id;

    SceneCallback onLoad;
    SceneCallback onUnload;
};
