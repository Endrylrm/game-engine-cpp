#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/scenes/SceneManager.hpp"
#include "engine/scenes/Scene.hpp"

class EntityAPI : public ManagerAPI<SceneManager>
{
public:
    template <std::derived_from<Entity> T, class... Args>
    static T *spawnEntity(Args &&...args)
    {
        Scene *currentScene = getManager().getCurrentScene();
        T *ptr = currentScene->spawnEntity<T>(std::forward<Args>(args)...);
        return ptr;
    }

    static Entity *spawnFromBlueprint(std::unique_ptr<Entity> entity)
    {
        Scene *currentScene = getManager().getCurrentScene();
        Entity *ptr = currentScene->spawnEntityBlueprint(std::move(entity));
        return ptr;
    }
};