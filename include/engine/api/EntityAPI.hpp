#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/scenes/SceneManager.hpp"
#include "engine/scenes/Scene.hpp"

class EntityAPI : public ManagerAPI<SceneManager>
{
public:
    static Entity *createEntity()
    {
        Scene *currentScene = getManager().getCurrentScene();
        Entity *ptr = currentScene->createEntity();
        return ptr;
    }

    static Entity *createEntity(std::unique_ptr<Entity> entityBlueprint)
    {
        Scene *currentScene = getManager().getCurrentScene();
        Entity *ptr = currentScene->createEntity(std::move(entityBlueprint));
        return ptr;
    }
};