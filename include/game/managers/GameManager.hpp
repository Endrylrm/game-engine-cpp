#pragma once
#include "engine/core/events/Connections.hpp"

class GameManager
{
public:
    ~GameManager() = default;
    void onStart();
    void onUpdate(float deltaTime);

private:
    void respawnPlayer();
    EventConnection playerDiedConnection;
};
