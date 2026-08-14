#include "game/ecs/systems/player/PlayerInputSystem.hpp"

#include <engine/api/InputAPI.hpp>

#include <game/ecs/components/player/PlayerInput.hpp>

void PlayerInputSystem::onUpdate(World &world, float deltaTime)
{
    for (auto [input] : world.view<PlayerInput>())
    {
        input.move = {0.0f, 0.0f};
        input.shoot = false;

        if (InputAPI::isKeyDown(KeyInput::W))
            input.move.y -= 1.0f;
        if (InputAPI::isKeyDown(KeyInput::S))
            input.move.y += 1.0f;
        if (InputAPI::isKeyDown(KeyInput::A))
            input.move.x -= 1.0f;
        if (InputAPI::isKeyDown(KeyInput::D))
            input.move.x += 1.0f;
        if (InputAPI::isKeyDown(KeyInput::Space))
            input.shoot = true;
    }
}
