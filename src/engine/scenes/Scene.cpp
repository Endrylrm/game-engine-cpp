#include "engine/scenes/Scene.hpp"

void Scene::init()
{
    renderSystem.setEventBus(&eventBus);
    entityManager.onInit();
    renderSystem.onInit();
    onInit();
}

void Scene::physics(float fixedDeltaTime)
{
    entityManager.onPhysics(fixedDeltaTime);
    onPhysics(fixedDeltaTime);
}

void Scene::preUpdate()
{
    eventBus.processEvents();
    entityManager.onPreUpdate();
    onPreUpdate();
}

void Scene::update(float deltaTime)
{
    entityManager.onUpdate(deltaTime);
    onUpdate(deltaTime);
}

void Scene::postUpdate()
{
    entityManager.onPostUpdate();
    onPostUpdate();
}

void Scene::render(Renderer &renderer)
{
    renderSystem.onRender(renderer);
    onRender(renderer);
}

void Scene::processLifecycle()
{
    eventBus.removeDeletedEvents();
    entityManager.removeDestroyedObjects();
    entityManager.processPendingSpawns();
    entityManager.processAwakeQueue();
    entityManager.processStartQueue();
}

void Scene::unload()
{
    entityManager.clearEntities();
    renderSystem.onUnload();
    onUnload();
}

Entity *Scene::createEntity()
{
    Entity *ptr = entityManager.createEntity();
    ptr->scene = this;
    return ptr;
}

Entity *Scene::createEntity(std::unique_ptr<Entity> entityBlueprint)
{
    Entity *ptr = entityManager.createEntity(std::move(entityBlueprint));
    ptr->scene = this;
    return ptr;
}
