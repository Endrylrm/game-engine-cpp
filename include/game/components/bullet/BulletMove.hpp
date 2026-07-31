#pragma once
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform.hpp"

class BulletMove : public Component
{
public:
    void onStart() override;
    void onUpdate(float deltaTime) override;

private:
    Transform *transform{};
    float speed{350.0f};
};
