#pragma once
#include "MeshData.hpp"

class Mesh
{
public:
    virtual ~Mesh() = default;
    virtual bool init(const MeshData &data) = 0;
    virtual bool isValid() const = 0;
};
