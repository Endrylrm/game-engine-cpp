#include "engine/entities/EntityManager.hpp"

void EntityManager::onInit()
{
}

void EntityManager::onPhysics(float fixedDeltaTime)
{
    for (auto &entity : entities)
    {
        if (!entity->isActive())
            continue;
        entity->onPhysics(fixedDeltaTime);
    }
}

void EntityManager::onPreUpdate()
{
    for (auto &entity : entities)
    {
        if (!entity->isActive())
            continue;
        entity->onPreUpdate();
    }
}

void EntityManager::onUpdate(float deltaTime)
{
    for (auto &entity : entities)
    {
        if (!entity->isActive())
            continue;
        entity->onUpdate(deltaTime);
    }
}

void EntityManager::onPostUpdate()
{
    for (auto &entity : entities)
    {
        if (!entity->isActive())
            continue;
        entity->onPostUpdate();
    }
}

void EntityManager::onRender(Renderer &renderer)
{
    for (auto &entity : entities)
    {
        if (!entity->isActive())
            continue;
        entity->onRender(renderer);
    }
}

void EntityManager::removeDestroyedObjects()
{
    for (auto &entity : entities)
    {
        if (entity->isPendingDestruction())
        {
            entity->onDestruction();
        }
    }

    std::erase_if(entities, [](const std::unique_ptr<Entity> &entity)
                  { return entity == nullptr || entity->isPendingDestruction(); });
}

void EntityManager::processPendingSpawns()
{
    if (spawnQueue.empty())
        return;

    for (auto &entity : spawnQueue)
    {
        if (entity->isPendingDestruction())
        {
            continue;
        }

        Entity *ptr = entity.get();
        entities.push_back(std::move(entity));
        ptr->markSpawned();
        awakeQueue.push_back(ptr);
    }

    spawnQueue.clear();
}

void EntityManager::processAwakeQueue()
{
    if (awakeQueue.empty())
        return;

    for (auto entity : awakeQueue)
    {
        // if the object get set to be destroyed, just skip it.
        // in case it's deactivated, we can awake the entity later.
        if (entity->isPendingDestruction() || entity->isDeactivated())
        {
            continue;
        }

        entity->markToStart();
        entity->onAwake();

        startQueue.push_back(entity);
    }

    awakeQueue.clear();
}

void EntityManager::processStartQueue()
{
    if (startQueue.empty())
        return;

    for (auto entity : startQueue)
    {
        // if the object get set to be destroyed, just skip it.
        // in case it's deactivated, we can start the entity later.
        if (entity->isPendingDestruction() || entity->isDeactivated())
        {
            continue;
        }

        entity->markActive();
        entity->onActivate();
        entity->markStarted();
        entity->onStart();
        entity->setVisible(true);
    }

    startQueue.clear();
}

Entity *EntityManager::findWithTag(const std::string &tag)
{
    for (auto &entity : entities)
    {
        if (entity->tag == tag)
            return entity.get();
    }

    return nullptr;
}

std::vector<Entity *> EntityManager::findAllWithTag(const std::string &tag)
{
    std::vector<Entity *> taggedEntities;

    for (auto &entity : entities)
    {
        if (entity->tag == tag)
            taggedEntities.push_back(entity.get());
    }

    return taggedEntities;
}

std::vector<std::unique_ptr<Entity>> &EntityManager::getEntities()
{
    return entities;
}