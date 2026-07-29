#include "game/components/player/PlayerController.hpp"

#include <iostream>
#include <string>

#include "engine/api/InputAPI.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/entities/Entity.hpp"

void PlayerController::onStart()
{
    transform = owner->getComponent<Transform2D>();
    transform->position.x = 375;
    transform->position.y = 450;
    std::cout << "Player Started!" << std::endl;
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
    std::cout << "Player Destroyed!" << std::endl;
}

void PlayerController::print()
{
    auto position = transform->position;
    std::cout << "my position is: " << position.x << "," << position.y << std::endl;
}
