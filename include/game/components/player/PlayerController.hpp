#pragma once
#include <string>

#include "engine/core/events/Connections.hpp"
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform.hpp"

class PlayerController : public Component
{
public:
    ~PlayerController() override = default;
    void onStart() override;
    void onUpdate(float deltaTime) override;
    void onDestruction() override;
    void print();

private:
    Transform *transform{};
    float speed{300.0f};
    EventConnection healthConnection;
};
