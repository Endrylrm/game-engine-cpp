#pragma once

class Shader
{
public:
    virtual ~Shader() = default;

    virtual bool is_valid() const = 0;
};
