#include "game/ecs/systems/common/ScreenClampSystem.hpp"

#include <algorithm>

#include <engine/api/WindowAPI.hpp>
#include <engine/ecs/components/BoxCollider.hpp>
#include <engine/ecs/components/Transform.hpp>

#include <game/ecs/components/common/ScreenClamp.hpp>

void ScreenClampSystem::onPostUpdate()
{
    for (auto [transform, collider, clamp] : registry.view<Transform, BoxCollider, ScreenClamp>())
    {
        if (clamp.horizontal)
            transform.position.x =
                std::clamp(transform.position.x, 0.0f, WindowAPI::getWidth() - collider.size.x);
        if (clamp.vertical)
            transform.position.y =
                std::clamp(transform.position.y, 0.0f, WindowAPI::getHeight() - collider.size.y);
    }
}
