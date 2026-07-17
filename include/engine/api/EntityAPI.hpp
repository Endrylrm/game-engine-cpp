#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/entities/EntityManager.hpp"
#include "engine/scenes/SceneManager.hpp"

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
};