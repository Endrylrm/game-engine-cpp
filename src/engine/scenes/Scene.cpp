#include "engine/scenes/Scene.hpp"

#include "engine/core/log/Log.hpp"

void Scene::load()
{
    if (onLoad)
        onLoad(*this);

    LOG_DEBUG("Scene '{}' Loaded!", id.index);
}

void Scene::unload()
{
    for (EntityId id : entities)
    {
        world.destroyEntity(id);
    }

    entities.clear();

    if (onUnload)
        onUnload(*this);

    LOG_DEBUG("Scene '{}' Unloaded!", id.index);
}

SceneId Scene::getId() const
{
    return id;
}

void Scene::setOnLoad(SceneCallback callback)
{
    onLoad = std::move(callback);
}

void Scene::setOnUnload(SceneCallback callback)
{
    onUnload = std::move(callback);
}

Entity Scene::createEntity()
{
    Entity entity = world.createEntity();
    entities.push_back(entity.getId());
    LOG_DEBUG("Entity handle created in Scene {}.", id.index);
    return entity;
}

std::vector<EntityId> Scene::getEntities()
{
    return entities;
}

World &Scene::getWorld()
{
    return world;
}
