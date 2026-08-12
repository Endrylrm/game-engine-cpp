#include "game/ecs/systems/player/PlayerMoveSystem.hpp"

#include <engine/api/InputAPI.hpp>
#include <engine/ecs/components/Transform.hpp>
#include <engine/ecs/components/Velocity.hpp>

#include <game/ecs/components/player/PlayerInput.hpp>

void PlayerMoveSystem::onUpdate(float deltaTime)
{
    for (auto [input, velocity] : registry.view<PlayerInput, Velocity>())
    {
        velocity.linear = input.move * 300.0f;
    }
}
