#include "game/components/player/PlayerController.hpp"

#include <iostream>
#include <string>

#include "engine/api/InputAPI.hpp"
#include "engine/core/log/Log.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/entities/Entity.hpp"

void PlayerController::onStart()
{
    transform = owner->getComponent<Transform>();
    transform->position.x = 375;
    transform->position.y = 450;
    LOG_DEBUG("Player started");
}

void PlayerController::onUpdate(float deltaTime)
{
    Vector2D direction = Vector2D::Zero();

    if (InputAPI::isKeyPressed(KeyInput::Space))
    {
        print();
    }
    if (InputAPI::isKeyDown(KeyInput::W))
    {
        direction.y -= 1.0f;
    }
    if (InputAPI::isKeyDown(KeyInput::S))
    {
        direction.y += 1.0f;
    }
    if (InputAPI::isKeyDown(KeyInput::A))
    {
        direction.x -= 1.0f;
    }
    if (InputAPI::isKeyDown(KeyInput::D))
    {
        direction.x += 1.0f;
    }

    direction.normalize();

    transform->position += direction * speed * deltaTime;
}

void PlayerController::onDestruction()
{
    LOG_DEBUG("Player destroyed!");
}

void PlayerController::print()
{
    auto position = transform->position;
    LOG_DEBUG("my position is: {},{}", position.x, position.y);
}
