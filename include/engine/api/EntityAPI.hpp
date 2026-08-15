#pragma once
#include <engine/api/ManagerAPI.hpp>
#include <engine/ecs/handle/Entity.hpp>
#include <engine/scenes/SceneManager.hpp>

class EntityAPI : public ManagerAPI<SceneManager>
{
public:
    static Entity createEntity()
    {
        return getManager().getMainScene()->createEntity();
    }
};
