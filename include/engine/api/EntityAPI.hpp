#pragma once
#include <string_view>

#include <engine/api/ManagerAPI.hpp>
#include <engine/ecs/handle/Entity.hpp>
#include <engine/scenes/Scene.hpp>
#include <engine/scenes/SceneManager.hpp>

class EntityAPI : public ManagerAPI<SceneManager>
{
public:
    static Entity createEntity()
    {
        return getMainScene()->createEntity();
    }

    static Entity createEntityAt(std::string_view id)
    {
        return getActiveScene(id)->createEntity();
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