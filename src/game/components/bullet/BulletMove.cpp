#include "game/components/bullet/BulletMove.hpp"

#include "engine/entities/Entity.hpp"

void BulletMove::onStart()
{
    transform = owner->getComponent<Transform>();
}

void BulletMove::onUpdate(float deltaTime)
{
    transform->position.y -= speed * deltaTime;
}