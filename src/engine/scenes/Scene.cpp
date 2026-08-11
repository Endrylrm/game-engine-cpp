#include "engine/scenes/Scene.hpp"

#include <engine/core/log/Log.hpp>
#include <engine/ecs/handle/Entity.hpp>

void Scene::init()
{
    systemManager.init();
    LOG_DEBUG("Scene '{}' Loaded and Initialized!", name.text());
}

void Scene::physics(float fixedDeltaTime)
{
    systemManager.physics(fixedDeltaTime);
}

void Scene::preUpdate()
{
    eventBus.processEvents();
    systemManager.preUpdate();
}

void Scene::update(float deltaTime)
{
    systemManager.update(deltaTime);
}

void Scene::postUpdate()
{
    systemManager.postUpdate();
}

void Scene::render(Renderer &renderer)
{
    systemManager.render(renderer);
}

void Scene::processLifecycle()
{
    eventBus.removeDeletedEvents();
    registry.processDestroyQueue();
}

void Scene::unload()
{
    systemManager.unload();
    LOG_DEBUG("Scene '{}' Unloaded!", name.text());
}

Entity Scene::createEntity()
{
    EntityId id = registry.createEntity();
    Entity entity = {id, this};
    LOG_DEBUG("Entity id: '{}', generation: {} created!", id.id, id.generation);
    return entity;
}

void Scene::queueDestroyEntity(EntityId entity)
{
    registry.destroyEntity(entity);
}
