#pragma once
#include <memory>
#include <queue>
#include <vector>

#include "engine/core/string/StringHandle.hpp"
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
    void removeDestroyedEntities();
    void processPendingSpawns();
    void processAwakeQueue();
    void processStartQueue();

    Entity *findWithTag(const StringHandle &tag);
    std::vector<Entity *> findAllWithTag(const StringHandle &tag);
    std::vector<std::unique_ptr<Entity>> &getEntities();
    void clear();

    Entity *create();
    Entity *create(std::unique_ptr<Entity> entityBlueprint);
    void queueDestroy(Entity *entity);

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
    void removeEntity(Entity *entity);

    std::vector<std::unique_ptr<Entity>> entities{};
    std::vector<std::unique_ptr<Entity>> spawnQueue{};
    std::vector<Entity *> awakeQueue{};
    std::vector<Entity *> startQueue{};
    std::vector<Entity *> destroyQueue{};
};
