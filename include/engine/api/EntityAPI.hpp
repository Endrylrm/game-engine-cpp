#pragma once
#include <string_view>

#include "engine/api/ManagerAPI.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/entities/EntityManager.hpp"
#include "engine/scenes/Scene.hpp"
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

    static Entity *createEntityAt(std::string_view id)
    {
        return getActiveScene(id)->createEntity();
    }

    static Entity *createEntityAt(std::string_view id, std::unique_ptr<Entity> entityBlueprint)
    {
        return getActiveScene(id)->createEntity(std::move(entityBlueprint));
    }

private:
    static Scene *getMainScene()
    {
        return getManager().getMainScene();
    }

    static Scene *getActiveScene(std::string_view id)
    {
        return getManager().getActiveScene(id);
    }
};