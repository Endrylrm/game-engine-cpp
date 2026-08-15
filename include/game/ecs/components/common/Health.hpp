#pragma once

struct Health
{
    Health() = default;
    Health(int hp) : current(hp), max(hp) {}
    Health(int currentHp, int maxHp) : current(currentHp), max(maxHp) {}

    int current{};
    int max{};
};
