#pragma once
#include "engine/core/math/Vector2DInt.hpp"

class Texture
{
public:
    virtual ~Texture() = default;

    virtual bool is_valid() const = 0;

    virtual Vector2DInt get_size() const = 0;
};
