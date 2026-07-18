#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/entities/EntityManager.hpp"
#include "engine/scenes/SceneManager.hpp"
#include "engine/scenes/Scene.hpp"

class EntityAPI : public ManagerAPI<SceneManager>
{
public:
    static Entity *createEntity()
    {
        return getEntityManager().createEntity();
    }

    static Entity *createEntity(std::unique_ptr<Entity> entityBlueprint)
    {
        return getEntityManager().createEntity(std::move(entityBlueprint));
    }

    template <std::derived_from<Scene> T>
    static Entity *createEntityAt()
    {
        return getEntityManagerAt<T>().createEntity();
    }

    template <std::derived_from<Scene> T>
    static Entity *createEntityAt(std::unique_ptr<Entity> entityBlueprint)
    {
        return getEntityManagerAt<T>().createEntity(std::move(entityBlueprint));
    }

    template <typename... Components, typename Func>
    static void forEach(Func &&func)
    {
        getEntityManager().forEach<Components...>(std::forward<Func>(func));
    }

    template <typename Func>
    static void forEachEntity(Func &&func)
    {
        getEntityManager().forEachEntity(std::forward<Func>(func));
    }

    template <typename... Components, typename Func>
    static void forEachComponent(Func &&func)
    {
        getEntityManager().forEachComponent<Components...>(std::forward<Func>(func));
    }

private:
    static EntityManager &getEntityManager()
    {
        return getManager().getMainScene()->getEntityManager();
    }

    template <std::derived_from<Scene> T>
    static EntityManager &getEntityManagerAt()
    {
        return getManager().getActiveScene<T>()->getEntityManager();
    }
};