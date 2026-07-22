#pragma once
#include "engine/entities/Entity.hpp"
#include "engine/core/events/Connections.hpp"

class GameManager
{
public:
    ~GameManager() = default;
    void onStart();
    void onUpdate(float deltaTime);

private:
    void respawnPlayer();
    Entity *player{};
    EventConnection playerDiedConnection;
};
