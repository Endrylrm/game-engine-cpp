#pragma once
#include "engine/core/math/Vector2DInt.hpp"

class Texture
{
public:
    virtual ~Texture() = default;

    virtual Vector2DInt getSize() const = 0;

    virtual bool isValid() const = 0;
};
