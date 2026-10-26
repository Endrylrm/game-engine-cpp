#pragma once
#include "engine/core/math/Matrix4.hpp"
#include "engine/core/math/Quaternion.hpp"
#include "engine/core/math/Vector3D.hpp"

struct Transform
{
    Transform() = default;
    Transform(Vector3D position) : position(position) {}
    Transform(Vector3D position, Quaternion rotation) : position(position), rotation(rotation) {}
    Transform(Vector3D position, Vector3D scale) : position(position), scale(scale) {}
    Transform(Vector3D position, Quaternion rotation, Vector3D scale)
        : position(position), rotation(rotation), scale(scale)
    {
    }
    Transform(float position_x, float position_y, float position_z)
        : position{position_x, position_y, position_z}
    {
    }
    Transform(
        float position_x,
        float position_y,
        float position_z,
        float rotation_x,
        float rotation_y,
        float rotation_z,
        float rotation_w
    )
        : position{position_x, position_y, position_z},
          rotation{rotation_x, rotation_y, rotation_z, rotation_w}
    {
    }
    Transform(
        float position_x,
        float position_y,
        float position_z,
        float rotation_x,
        float rotation_y,
        float rotation_z,
        float rotation_w,
        float scale_x,
        float scale_y,
        float scale_z
    )
        : position{position_x, position_y, position_z},
          rotation{rotation_x, rotation_y, rotation_z, rotation_w},
          scale{scale_x, scale_y, scale_z}
    {
    }

    Matrix4 to_matrix() const
    {
        return Matrix4::translation(position) * Matrix4::rotation(rotation) * Matrix4::scale(scale);
    }

    Vector3D position{};
    Quaternion rotation{};
    Vector3D scale{Vector3D::one()};
};
