#pragma once
#include <vector>

#include <engine/ecs/handle/Entity.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/ecs/world/World.hpp>

#include "SceneId.hpp"

class Scene
{
public:
    using SceneCallback = void (*)(Scene &);

    Scene(SceneId id, World &world) : id(id), world(world) {}
    ~Scene() = default;

    void load();
    void unload();

    Entity createEntity();
    std::vector<EntityId> getEntities();

    SceneId getId() const;

    void setOnLoad(SceneCallback callback);
    void setOnUnload(SceneCallback callback);

    World &getWorld();

private:
    World &world;
    SceneId id;

    std::vector<EntityId> entities{};

    SceneCallback onLoad = nullptr;
    SceneCallback onUnload = nullptr;
};
