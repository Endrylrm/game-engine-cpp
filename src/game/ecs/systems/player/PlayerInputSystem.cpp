#include "game/ecs/systems/player/PlayerInputSystem.hpp"

#include "engine/api/InputAPI.hpp"

#include "game/ecs/components/player/PlayerInput.hpp"

void PlayerInputSystem::on_update(World &world, float delta_time)
{
    for (auto [input] : world.view<PlayerInput>())
    {
        input.move = {0.0f, 0.0f};
        input.shoot = false;

        if (InputAPI::is_key_down(KeyInput::W))
            input.move.y -= 1.0f;
        if (InputAPI::is_key_down(KeyInput::S))
            input.move.y += 1.0f;
        if (InputAPI::is_key_down(KeyInput::A))
            input.move.x -= 1.0f;
        if (InputAPI::is_key_down(KeyInput::D))
            input.move.x += 1.0f;
        if (InputAPI::is_key_down(KeyInput::Space))
            input.shoot = true;
    }
}
