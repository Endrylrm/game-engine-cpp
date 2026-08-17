#pragma once
#include <cstdint>
#include <string>

class Texture
{
public:
    virtual ~Texture() = default;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    virtual bool isValid() const = 0;
};
