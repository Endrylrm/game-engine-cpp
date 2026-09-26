#pragma once

class Shader
{
public:
    virtual ~Mesh() = default;
    virtual bool isValid() const = 0;
};
