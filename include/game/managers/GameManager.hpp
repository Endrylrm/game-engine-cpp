#pragma once
#include "engine/core/events/Connections.hpp"
#include "engine/entities/Entity.hpp"

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
