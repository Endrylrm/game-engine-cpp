#include "game/components/common/Health.hpp"
#include "engine/entities/Entity.hpp"
#include <iostream>

void Health::onAwake()
{
    if (maxHP == 0)
    {
        maxHP = hp;
    }
}

void Health::onUpdate(float deltaTime)
{
    if (hp > maxHP)
    {
        hp = maxHP;
    }

    if (hp <= minHP)
    {
        hp = minHP;
        onDead.emit();
        owner->markForDestruction();
    }
}

void Health::takeDamage(int damage)
{
    hp -= damage;
    onHealthChanged.emit(hp);
}

int Health::getCurrentHP()
{
    return hp;
}

int Health::getMaxHP()
{
    return maxHP;
}