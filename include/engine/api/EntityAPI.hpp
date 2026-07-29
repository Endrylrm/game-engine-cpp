#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/entities/EntityManager.hpp"
#include "engine/scenes/Scene.hpp"
#include "engine/scenes/SceneConcept.hpp"
#include "engine/scenes/SceneManager.hpp"

class EntityAPI : public ManagerAPI<SceneManager>
{
public:
    static Entity *createEntity()
    {
        return getMainScene()->createEntity();
    }

    static Entity *createEntity(std::unique_ptr<Entity> entityBlueprint)
    {
        return getMainScene()->createEntity(std::move(entityBlueprint));
    }

    template <SceneConcept SceneType>
    static Entity *createEntityAt()
    {
        return getActiveScene<SceneType>()->createEntity();
    }

    template <SceneConcept SceneType>
    static Entity *createEntityAt(std::unique_ptr<Entity> entityBlueprint)
    {
        return getActiveScene<SceneType>()->createEntity(std::move(entityBlueprint));
    }

private:
    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }

    template <SceneConcept SceneType>
    static Scene *getActiveScene()
    {
        return getManager().getActiveScene<SceneType>();
    }
};