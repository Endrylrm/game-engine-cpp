#pragma once

class Mesh
{
public:
    virtual ~Mesh() = default;

    virtual bool is_valid() const = 0;
};
