#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "engine/entities/Entity.hpp"

class EntityManager
{
public:
    ~EntityManager() = default;

    void onInit();
    void onPhysics(float fixedDeltaTime);
    void onPreUpdate();
    void onUpdate(float deltaTime);
    void onPostUpdate();
    void removeDestroyedObjects();
    void processPendingSpawns();
    void processAwakeQueue();
    void processStartQueue();

    Entity *findWithTag(const std::string &tag);
    std::vector<Entity *> findAllWithTag(const std::string &tag);
    std::vector<std::unique_ptr<Entity>> &getEntities();
    void clearEntities();

    Entity *createEntity()
    {
        auto entity = std::make_unique<Entity>();

        Entity *ptr = entity.get();

        spawnQueue.push_back(std::move(entity));

        return ptr;
    }

    Entity *createEntity(std::unique_ptr<Entity> entityBlueprint)
    {
        Entity *ptr = entityBlueprint.get();

        spawnQueue.push_back(std::move(entityBlueprint));

        return ptr;
    }

    template <typename... Components, typename Func>
    void forEach(Func &&func)
    {
        for (auto &entity : entities)
        {
            if ((entity->hasComponent<Components>() && ...))
            {
                func(*entity, *entity->getComponent<Components>()...);
            }
        }
    }

    template <typename Func>
    void forEachEntity(Func &&func)
    {
        for (auto &entity : entities)
            func(*entity);
    }

    template <typename... Components, typename Func>
    void forEachComponent(Func &&func)
    {
        for (auto &entity : entities)
        {
            if ((entity->hasComponent<Components>() && ...))
            {
                func(*entity->getComponent<Components>()...);
            }
        }
    }

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> spawnQueue;
    std::vector<Entity *> awakeQueue;
    std::vector<Entity *> startQueue;
};
