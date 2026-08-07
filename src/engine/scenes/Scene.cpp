#include "engine/scenes/Scene.hpp"

#include <engine/core/log/Log.hpp>

void Scene::init()
{
    renderSystem.setEventBus(&eventBus);
    entityManager.onInit();
    renderSystem.onInit();
    LOG_DEBUG("Scene '{}' Loaded and Initialized!", name.text());
}

void Scene::physics(float fixedDeltaTime)
{
    entityManager.onPhysics(fixedDeltaTime);
}

void Scene::preUpdate()
{
    eventBus.processEvents();
    entityManager.onPreUpdate();
}

void Scene::update(float deltaTime)
{
    entityManager.onUpdate(deltaTime);
}

void Scene::postUpdate()
{
    entityManager.onPostUpdate();
}

void Scene::render(Renderer &renderer)
{
    renderSystem.onRender(renderer);
}

void Scene::processLifecycle()
{
    eventBus.removeDeletedEvents();
    entityManager.removeDestroyedEntities();
    entityManager.processPendingSpawns();
    entityManager.processAwakeQueue();
    entityManager.processStartQueue();
}

void Scene::unload()
{
    entityManager.clear();
    renderSystem.onUnload();
    LOG_DEBUG("Scene '{}' Unloaded!", name.text());
}

Entity *Scene::createEntity()
{
    Entity *ptr = entityManager.create();
    ptr->scene = this;
    return ptr;
}

Entity *Scene::createEntity(std::unique_ptr<Entity> entityBlueprint)
{
    Entity *ptr = entityManager.create(std::move(entityBlueprint));
    ptr->scene = this;
    return ptr;
}

void Scene::queueDestroyEntity(Entity *entity)
{
    entityManager.queueDestroy(entity);
}
