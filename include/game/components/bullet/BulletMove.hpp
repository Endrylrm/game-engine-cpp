#pragma once
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform2D.hpp"

class BulletMove : public Component
{
public:
    void onStart() override;
    void onUpdate(float deltaTime) override;

private:
    Transform2D *transform = nullptr;
    float speed = 350.0f;
};
