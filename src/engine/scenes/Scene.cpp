#include "engine/scenes/Scene.hpp"

#include "engine/core/log/Log.hpp"

void Scene::load()
{
    if (on_load)
        on_load(*this);

    LOG_DEBUG("Scene '{}' Loaded!", id.index);
}

void Scene::unload()
{
    for (EntityId id : entities)
    {
        world.destroy_entity(id);
    }

    entities.clear();

    if (on_unload)
        on_unload(*this);

    LOG_DEBUG("Scene '{}' Unloaded!", id.index);
}

SceneId Scene::get_id() const
{
    return id;
}

void Scene::set_on_load(SceneCallback callback)
{
    on_load = std::move(callback);
}

void Scene::set_on_unload(SceneCallback callback)
{
    on_unload = std::move(callback);
}

Entity Scene::create_entity()
{
    Entity entity = world.create_entity();
    entities.push_back(entity.get_id());
    LOG_DEBUG("Entity handle created in Scene {}.", id.index);
    return entity;
}

std::vector<EntityId> Scene::get_entities()
{
    return entities;
}

World &Scene::get_world()
{
    return world;
}
