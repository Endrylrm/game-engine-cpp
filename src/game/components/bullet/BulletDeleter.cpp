#include "game/components/bullet/BulletDeleter.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/api/WindowAPI.hpp"
#include <iostream>

void BulletDeleter::onStart()
{
    transform = owner->getComponent<Transform2D>();
}

void BulletDeleter::onUpdate(float deltaTime)
{
    if (isOutOfBounds())
    {
        owner->markForDestruction();
    }
}

bool BulletDeleter::isOutOfBounds()
{
    if (transform->position.y < -300.0f)
    {
        return true;
    }
    if (transform->position.y > WindowAPI::getHeight() + 300.0f)
    {
        return true;
    }
    if (transform->position.x < -300.0f)
    {
        return true;
    }
    if (transform->position.x > WindowAPI::getWidth() + 300.0f)
    {
        return true;
    }
    return false;
}

void BulletDeleter::onDestruction()
{
    std::cout << "bullet destroyed" << std::endl;
}