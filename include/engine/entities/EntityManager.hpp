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

    Entity *createEntity();
    Entity *createEntity(std::unique_ptr<Entity> entityBlueprint);

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

    template <typename... Components>
    std::vector<Entity *> getEntitiesWith()
    {
        std::vector<Entity *> entitiesWith{};

        for (auto &entity : entities)
        {
            if ((entity->hasComponent<Components>() && ...))
            {
                entitiesWith.push_back(entity.get());
            }
        }

        return entitiesWith;
    }

    template <typename... Components>
    std::vector<Entity *> getEntitiesWithAny()
    {
        std::vector<Entity *> entitiesWith{};

        for (auto &entity : entities)
        {
            if ((entity->hasComponent<Components>() || ...))
            {
                entitiesWith.push_back(entity.get());
            }
        }

        return entitiesWith;
    }

private:
    std::vector<std::unique_ptr<Entity>> entities{};
    std::vector<std::unique_ptr<Entity>> spawnQueue{};
    std::vector<Entity *> awakeQueue{};
    std::vector<Entity *> startQueue{};
};
