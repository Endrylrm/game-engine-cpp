#pragma once
#include <engine/core/math/Quaternion.hpp>
#include <engine/core/math/Vector3D.hpp>

struct Transform
{
    Transform() = default;
    Transform(Vector3D position) : position(position) {}
    Transform(Vector3D position, Quaternion rotation) : position(position), rotation(rotation) {}
    Transform(Vector3D position, Quaternion rotation, Vector3D scale)
        : position(position), rotation(rotation), scale(scale)
    {
    }
    Transform(float positionX, float positionY, float positionZ)
        : position{positionX, positionY, positionZ}
    {
    }
    Transform(
        float positionX,
        float positionY,
        float positionZ,
        float rotationX,
        float rotationY,
        float rotationZ,
        float rotationW
    )
        : position{positionX, positionY, positionZ},
          rotation{rotationX, rotationY, rotationZ, rotationW}
    {
    }
    Transform(
        float positionX,
        float positionY,
        float positionZ,
        float rotationX,
        float rotationY,
        float rotationZ,
        float rotationW,
        float scaleX,
        float scaleY,
        float scaleZ
    )
        : position{positionX, positionY, positionZ},
          rotation{rotationX, rotationY, rotationZ, rotationW},
          scale{scaleX, scaleY, scaleZ}
    {
    }

    Vector3D position{};
    Quaternion rotation{};
    Vector3D scale{Vector3D::One()};
};
