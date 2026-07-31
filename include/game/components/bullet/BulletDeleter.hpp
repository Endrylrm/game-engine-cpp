#pragma once
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform.hpp"

class BulletDeleter : public Component
{
public:
    void onStart() override;
    void onUpdate(float deltaTime) override;
    void onDestruction() override;

private:
    bool isOutOfBounds();
    Transform *transform{};
};
