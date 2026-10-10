#pragma once

class Shader
{
public:
    virtual ~Shader() = default;

    virtual bool isValid() const = 0;
};
