#pragma once
#include "engine/Game.hpp"

class SpaceShooterGame : public Game
{
public:
    ~SpaceShooterGame() override = default;
    void onInit() override;
    void onShutdown() override;
};
