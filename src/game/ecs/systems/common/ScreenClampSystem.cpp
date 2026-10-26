#include "game/ecs/systems/common/ScreenClampSystem.hpp"

#include "engine/api/WindowAPI.hpp"
#include "engine/core/math/Math.hpp"
#include "engine/ecs/components/BoxCollider.hpp"
#include "engine/ecs/components/Transform.hpp"

#include "game/ecs/components/common/ScreenClamp.hpp"

void ScreenClampSystem::on_post_update(World &world)
{
    for (auto [transform, collider, clamp] : world.view<Transform, BoxCollider, ScreenClamp>())
    {
        if (clamp.horizontal)
            transform.position.x =
                Math::clamp(transform.position.x, 0.0f, WindowAPI::get_width() - collider.size.x);
        if (clamp.vertical)
            transform.position.y =
                Math::clamp(transform.position.y, 0.0f, WindowAPI::get_height() - collider.size.y);
    }
}
