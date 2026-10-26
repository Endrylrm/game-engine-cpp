#include "game/ecs/systems/player/PlayerMoveSystem.hpp"

#include "engine/ecs/components/Velocity.hpp"

#include "game/ecs/components/player/PlayerInput.hpp"

void PlayerMoveSystem::on_update(World &world, float delta_time)
{
    for (auto [input, velocity] : world.view<PlayerInput, Velocity>())
    {
        velocity.linear = input.move * 300.0f;
    }
}
