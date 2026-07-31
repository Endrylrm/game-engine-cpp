#pragma once
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform.hpp"

class ClampUD : public Component
{
public:
    ~ClampUD() override = default;
    void onStart() override;
    void onPostUpdate() override;

private:
    Transform *transform{};
};
