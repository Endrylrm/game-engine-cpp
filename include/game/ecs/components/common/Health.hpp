#pragma once

struct Health
{
    Health() = default;
    Health(int hp) : current(hp), max(hp) {}
    Health(int current_hp, int max_hp) : current(current_hp), max(max_hp) {}

    int current{};
    int max{};
};
