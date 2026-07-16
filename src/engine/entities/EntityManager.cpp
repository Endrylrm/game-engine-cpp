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

    while (!spawnQueue.empty())
    {
        Entity *entity = spawnQueue.front();

        if (entity->isPendingDestruction())
        {
            spawnQueue.pop();
            continue;
        }

        entity->markSpawned();
        awakeQueue.push(entity);
        spawnQueue.pop();
    }
}

void EntityManager::processAwakeQueue()
{
    if (awakeQueue.empty())
        return;

    while (!awakeQueue.empty())
    {
        Entity *entity = awakeQueue.front();
        // if the object get set to be destroyed, just skip it.
        // in case it's deactivated, we can awake the entity later.
        if (entity->isPendingDestruction() || entity->isDeactivated())
        {
            awakeQueue.pop();
            continue;
        }

        entity->markToStart();
        entity->onAwake();

        startQueue.push(entity);
        awakeQueue.pop();
    }
}

void EntityManager::processStartQueue()
{
    if (startQueue.empty())
        return;

    while (!startQueue.empty())
    {
        Entity *entity = startQueue.front();
        // if the object get set to be destroyed, just skip it.
        // in case it's deactivated, we can start the entity later.
        if (entity->isPendingDestruction() || entity->isDeactivated())
        {
            startQueue.pop();
            continue;
        }

        entity->markActive();
        entity->onActivate();
        entity->markStarted();
        entity->onStart();
        entity->setVisible(true);
        startQueue.pop();
    }
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