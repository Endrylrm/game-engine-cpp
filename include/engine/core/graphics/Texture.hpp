#pragma once
#include <cstdint>
#include <string>

class Texture
{
public:
    virtual ~Texture() = default;

    virtual void bind(uint32_t slot = 0) const = 0;
    virtual void *getNativeHandle() const = 0;

    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;

    virtual bool isValid() const = 0;
};
