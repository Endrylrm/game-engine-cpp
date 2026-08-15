#include "engine/scenes/Scene.hpp"

#include <engine/core/log/Log.hpp>
#include <engine/ecs/components/Scoped.hpp>
#include <engine/ecs/handle/Entity.hpp>

void Scene::load()
{
    if (onLoad)
        onLoad(*this);

    LOG_DEBUG("Scene '{}' Loaded!", id.value);
}

void Scene::unload()
{
    if (onUnload)
        onUnload(*this);

    world.destroyScopedEntities(id.value);
    LOG_DEBUG("Scene '{}' Unloaded!", id.value);
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

World &Scene::getWorld()
{
    return world;
}

Entity Scene::createEntity()
{
    Entity entity = world.createEntity();
    entity.addComponent<Scoped>(id.value);
    LOG_DEBUG("Entity handle created in Scene {}.", id.value);
    return entity;
}
