#pragma once
#include "engine/core/events/Connections.hpp"
#include "engine/entities/components/Component.hpp"

class GameManager : public Component
{
public:
    ~GameManager() = default;
    void onStart() override;
    void onUpdate(float deltaTime) override;

private:
    void respawnPlayer();
    EventConnection playerDiedConnection;
};
