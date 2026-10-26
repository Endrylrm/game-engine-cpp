#include "engine/camera/Camera.hpp"

#include "engine/core/log/Log.hpp"

Camera::Camera()
{
    update_view_matrix();
    update_projection_matrix();
}

Camera Camera::create_perspective(
    const Vector3D &position,
    const Quaternion &rotation,
    float fov,
    float aspect_ratio,
    float near_plane,
    float far_plane
)
{
    Camera camera;
    camera.position = position;
    camera.rotation = rotation;

    camera.projection_type = ProjectionType::Perspective;

    camera.perspective.fov = fov;
    camera.perspective.aspect_ratio = aspect_ratio;

    camera.perspective.near_plane = near_plane;
    camera.perspective.far_plane = far_plane;

    camera.update_view_matrix();
    camera.update_projection_matrix();
    return camera;
}

Camera Camera::create_orthographic(
    const Vector3D &position,
    const Quaternion &rotation,
    float orthographic_size,
    float aspect_ratio,
    float near_plane,
    float far_plane
)
{
    Camera camera;
    camera.position = position;
    camera.rotation = rotation;

    camera.projection_type = ProjectionType::Orthographic;

    const float HALF_HEIGHT = orthographic_size;
    const float HALF_WIDTH = orthographic_size * aspect_ratio;

    camera.orthographic.left = -HALF_WIDTH;
    camera.orthographic.right = HALF_WIDTH;
    camera.orthographic.bottom = HALF_HEIGHT;
    camera.orthographic.top = -HALF_HEIGHT;

    camera.orthographic.near_plane = near_plane;
    camera.orthographic.far_plane = far_plane;

    camera.update_view_matrix();
    camera.update_projection_matrix();
    return camera;
}

Camera Camera::create_orthographic2_d(
    const Vector3D &position,
    const Quaternion &rotation,
    float width,
    float height,
    float near_plane,
    float far_plane
)
{
    Camera camera;
    camera.position = position;
    camera.rotation = rotation;

    camera.projection_type = ProjectionType::Orthographic;

    camera.orthographic.left = 0.0f;
    camera.orthographic.right = width;
    camera.orthographic.top = 0.0f;
    camera.orthographic.bottom = height;

    camera.orthographic.near_plane = near_plane;
    camera.orthographic.far_plane = far_plane;

    camera.update_view_matrix();
    camera.update_projection_matrix();
    return camera;
}

const Vector3D &Camera::get_position() const
{
    return position;
}

void Camera::set_position(const Vector3D &new_position)
{
    position = new_position;
    update_view_matrix();
}

const Quaternion &Camera::get_rotation() const
{
    return rotation;
}

void Camera::set_rotation(const Quaternion &new_rotation)
{
    rotation = new_rotation.normalized();
    update_view_matrix();
}

ProjectionType Camera::get_projection_type() const
{
    return projection_type;
}

void Camera::set_projection_type(ProjectionType new_projection_type)
{
    projection_type = new_projection_type;
    update_projection_matrix();
}

float Camera::get_field_of_view() const
{
    return perspective.fov;
}

void Camera::set_field_of_view(float new_fov)
{
    perspective.fov = new_fov;
    update_projection_matrix();
}

float Camera::get_aspect_ratio() const
{
    return perspective.aspect_ratio;
}

void Camera::set_aspect_ratio(float new_aspect_ratio)
{
    perspective.aspect_ratio = new_aspect_ratio;
    update_projection_matrix();
}

float Camera::get_near_plane() const
{
    switch (projection_type)
    {
    case ProjectionType::Perspective:
        return perspective.near_plane;
    case ProjectionType::Orthographic:
        return orthographic.near_plane;
    }
    return 0.0f;
}

void Camera::set_near_plane(float new_near_plane)
{
    switch (projection_type)
    {
    case ProjectionType::Perspective:
        perspective.near_plane = new_near_plane;
        break;
    case ProjectionType::Orthographic:
        orthographic.near_plane = new_near_plane;
        break;
    }
    update_projection_matrix();
}

float Camera::get_far_plane() const
{
    switch (projection_type)
    {
    case ProjectionType::Perspective:
        return perspective.far_plane;
    case ProjectionType::Orthographic:
        return orthographic.far_plane;
    }
    return 0.0f;
}

void Camera::set_far_plane(float new_far_plane)
{
    switch (projection_type)
    {
    case ProjectionType::Perspective:
        perspective.far_plane = new_far_plane;
        break;
    case ProjectionType::Orthographic:
        orthographic.far_plane = new_far_plane;
        break;
    }
    update_projection_matrix();
}

float Camera::get_orthographic_left() const
{
    return orthographic.left;
}

void Camera::set_orthographic_left(float new_orthographic_left)
{
    orthographic.left = new_orthographic_left;
    update_projection_matrix();
}

float Camera::get_orthographic_right() const
{
    return orthographic.right;
}

void Camera::set_orthographic_right(float new_orthographic_right)
{
    orthographic.right = new_orthographic_right;
    update_projection_matrix();
}

float Camera::get_orthographic_bottom() const
{
    return orthographic.bottom;
}

void Camera::set_orthographic_bottom(float new_orthographic_bottom)
{
    orthographic.bottom = new_orthographic_bottom;
    update_projection_matrix();
}

float Camera::get_orthographic_top() const
{
    return orthographic.top;
}

void Camera::set_orthographic_top(float new_orthographic_top)
{
    orthographic.top = new_orthographic_top;
    update_projection_matrix();
}

Vector3D Camera::forward() const
{
    return rotation.rotate(Vector3D::forward());
}

Vector3D Camera::right() const
{
    return rotation.rotate(Vector3D::right());
}

Vector3D Camera::up() const
{
    return rotation.rotate(Vector3D::up());
}

const Matrix4 &Camera::get_view_matrix() const
{
    return view_matrix;
}

const Matrix4 &Camera::get_projection_matrix() const
{
    return projection_matrix;
}

void Camera::update_view_matrix()
{
    const Quaternion INVERSE_ROTATION = rotation.conjugate();

    const Matrix4 ROTATION = Matrix4::rotation(INVERSE_ROTATION);
    const Matrix4 TRANSLATION = Matrix4::translation(-position);

    view_matrix = ROTATION * TRANSLATION;
}

void Camera::update_projection_matrix()
{
    switch (projection_type)
    {
    case ProjectionType::Perspective:
    {
        projection_matrix = Matrix4::perspective(
            perspective.fov, perspective.aspect_ratio, perspective.near_plane, perspective.far_plane
        );
        break;
    }
    case ProjectionType::Orthographic:
    {
        projection_matrix = Matrix4::orthographic(
            orthographic.left,
            orthographic.right,
            orthographic.bottom,
            orthographic.top,
            orthographic.near_plane,
            orthographic.far_plane
        );
        break;
    }
    default:
        LOG_ERROR("Unknown Projection Type...");
        break;
    }
}
