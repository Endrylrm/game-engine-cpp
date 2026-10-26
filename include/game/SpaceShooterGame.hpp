#pragma once
#include "engine/Game.hpp"

class SpaceShooterGame final : public Game
{
public:
    ~SpaceShooterGame() override = default;
    void on_init() override;
    void on_shutdown() override;
};
