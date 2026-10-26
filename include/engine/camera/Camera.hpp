#pragma once

#include "engine/core/math/Matrix4.hpp"
#include "engine/core/math/Quaternion.hpp"
#include "engine/core/math/Vector3D.hpp"

enum class ProjectionType
{
    Perspective,
    Orthographic
};

struct PerspectiveProjection
{
    float fov{45.0f};
    float aspect_ratio{16.0f / 9.0f};
    float near_plane{0.1f};
    float far_plane{100.0f};
};

struct OrthographicProjection
{
    float left{};
    float right{};
    float bottom{};
    float top{};
    float near_plane{0.1f};
    float far_plane{100.0f};
};

class Camera
{
public:
    Camera();

    static Camera create_perspective(
        const Vector3D &position,
        const Quaternion &rotation,
        float fov,
        float aspect_ratio,
        float near_plane,
        float far_plane
    );

    static Camera create_orthographic(
        const Vector3D &position,
        const Quaternion &rotation,
        float orthographic_size,
        float aspect_ratio,
        float near_plane,
        float far_plane
    );

    static Camera create_orthographic2_d(
        const Vector3D &position,
        const Quaternion &rotation,
        float width,
        float height,
        float near_plane,
        float far_plane
    );

    const Vector3D &get_position() const;
    void set_position(const Vector3D &new_position);

    const Quaternion &get_rotation() const;
    void set_rotation(const Quaternion &new_rotation);

    ProjectionType get_projection_type() const;
    void set_projection_type(ProjectionType new_projection_type);

    float get_field_of_view() const;
    void set_field_of_view(float new_fov);

    float get_aspect_ratio() const;
    void set_aspect_ratio(float new_aspect_ratio);

    float get_near_plane() const;
    void set_near_plane(float new_near_plane);

    float get_far_plane() const;
    void set_far_plane(float new_far_plane);

    float get_orthographic_left() const;
    void set_orthographic_left(float new_orthographic_left);

    float get_orthographic_right() const;
    void set_orthographic_right(float new_orthographic_right);

    float get_orthographic_bottom() const;
    void set_orthographic_bottom(float new_orthographic_bottom);

    float get_orthographic_top() const;
    void set_orthographic_top(float new_orthographic_top);

    Vector3D forward() const;
    Vector3D right() const;
    Vector3D up() const;

    const Matrix4 &get_view_matrix() const;
    const Matrix4 &get_projection_matrix() const;

private:
    void update_view_matrix();
    void update_projection_matrix();

    Vector3D position{};
    Quaternion rotation{Quaternion::identity()};

    ProjectionType projection_type{ProjectionType::Perspective};

    PerspectiveProjection perspective{};
    OrthographicProjection orthographic{};

    Matrix4 view_matrix{Matrix4::identity()};
    Matrix4 projection_matrix{Matrix4::identity()};
};
