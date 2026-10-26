#pragma once
#include <vector>

#include "engine/ecs/handle/Entity.hpp"
#include "engine/ecs/registry/entities/EntityId.hpp"
#include "engine/ecs/world/World.hpp"

#include "SceneId.hpp"

class Scene
{
public:
    using SceneCallback = void (*)(Scene &);

    Scene(SceneId id, World &world) : id(id), world(world) {}
    ~Scene() = default;

    void load();
    void unload();

    Entity create_entity();
    std::vector<EntityId> get_entities();

    SceneId get_id() const;

    void set_on_load(SceneCallback callback);
    void set_on_unload(SceneCallback callback);

    World &get_world();

private:
    World &world;
    SceneId id;

    std::vector<EntityId> entities{};

    SceneCallback on_load = nullptr;
    SceneCallback on_unload = nullptr;
};
