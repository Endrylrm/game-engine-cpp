#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "engine/entities/Entity.hpp"
#include "engine/core/graphics/Renderer.hpp"

class EntityManager
{
public:
    ~EntityManager() = default;

    void onInit();
    void onPhysics(float fixedDeltaTime);
    void onPreUpdate();
    void onUpdate(float deltaTime);
    void onPostUpdate();
    void onRender(Renderer &renderer);
    void removeDestroyedObjects();
    void processPendingSpawns();
    void processAwakeQueue();
    void processStartQueue();

    Entity *findWithTag(const std::string &tag);
    std::vector<Entity *> findAllWithTag(const std::string &tag);
    std::vector<std::unique_ptr<Entity>> &getEntities();

    template <std::derived_from<Entity> T, typename... Args>
    T *spawnEntity(Args &&...args)
    {
        auto entity = std::make_unique<T>(std::forward<Args>(args)...);

        T *ptr = entity.get();

        entities.push_back(std::move(entity));
        spawnQueue.push(entities.back().get());

        return ptr;
    }

    Entity *spawnEntityBlueprint(std::unique_ptr<Entity> entity)
    {
        Entity *ptr = entity.get();

        entities.push_back(std::move(entity));
        spawnQueue.push(entities.back().get());

        return ptr;
    }

    template <typename... Components, typename Func>
    void forEach(Func &&func)
    {
        for (auto &entity : entities)
        {
            if ((entity->hasComponent<Components>() && ...))
            {
                func(*entity, entity->getComponent<Components>()...);
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
                func(entity->getComponent<Components>()...);
            }
        }
    }

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::queue<Entity *> spawnQueue;
    std::queue<Entity *> awakeQueue;
    std::queue<Entity *> startQueue;
};
