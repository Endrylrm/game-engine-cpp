#pragma once
#include <memory>
#include "engine/Game.hpp"

class SpaceShooterGame : public Game
{
public:
    ~SpaceShooterGame() override = default;
    void onInit() override;
    void onShutdown() override;
};
