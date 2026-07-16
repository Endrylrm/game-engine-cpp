#pragma once
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/Transform2D.hpp"

class ClampLR : public Component
{
public:
    ~ClampLR() override = default;
    void onStart() override;
    void onPostUpdate() override;

private:
    Transform2D *transform = nullptr;
};
