#pragma once

struct Health
{
    Health() = default;
    Health(int hp) : currentHp(hp), maxHp(hp) {}
    Health(int currentHp, int maxHp) : currentHp(currentHp), maxHp(maxHp) {}

    int currentHp{};
    int maxHp{};
};
