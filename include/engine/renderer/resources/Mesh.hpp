#pragma once

class Mesh
{
public:
    virtual ~Mesh() = default;

    virtual bool isValid() const = 0;
};
