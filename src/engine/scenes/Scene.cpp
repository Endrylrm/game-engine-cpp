#include "engine/scenes/Scene.hpp"

#include <engine/core/log/Log.hpp>
#include <engine/ecs/components/SceneTag.hpp>
#include <engine/ecs/handle/Entity.hpp>

void Scene::unload()
{
    world.destroySceneEntities(id);
    LOG_DEBUG("Scene '{}' Unloaded!", id.value);
}

Entity Scene::createEntity()
{
    Entity entity = world.createEntity();
    entity.addComponent<SceneTag>(id);
    LOG_DEBUG("Entity handle created in Scene {}.", id.value);
    return entity;
}
