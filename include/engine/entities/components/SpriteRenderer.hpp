#pragma once
#include <string>
#include "engine/entities/components/Component.hpp"
#include "engine/core/math/Rect2D.hpp"

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(const std::string &textureId) : textureId(textureId) {}
    ~SpriteRenderer() override = default;

    std::string textureId;
};
