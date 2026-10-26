#include "game/ecs/systems/common/OutOfBoundsSystem.hpp"

#include "engine/api/WindowAPI.hpp"
#include "engine/core/log/Log.hpp"
#include "engine/ecs/components/Transform.hpp"

#include "game/ecs/components/common/Dead.hpp"
#include "game/ecs/components/common/OutOfBounds.hpp"

void OutOfBoundsSystem::on_update(World &world, float delta_time)
{
    for (auto [entity, transform, outOfBounds] :
         world.view<Transform, OutOfBounds>().with_entities())
    {
        if (is_out_of_bounds(transform.position, outOfBounds.margin))
        {
            world.add_component<Dead>(entity);
        }
    }
}

bool OutOfBoundsSystem::is_out_of_bounds(Vector2D position, float margin)
{
    if (position.y < -margin)
    {
        return true;
    }
    if (position.y > WindowAPI::get_height() + margin)
    {
        return true;
    }
    if (position.x < -margin)
    {
        return true;
    }
    if (position.x > WindowAPI::get_width() + margin)
    {
        return true;
    }
    return false;
}
