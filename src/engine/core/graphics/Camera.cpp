#include "engine/core/graphics/Camera.hpp"

#include <engine/core/log/Log.hpp>

Camera::Camera()
{
    updateViewMatrix();
    updateProjectionMatrix();
}

Camera Camera::createPerspective(
    const Vector3D &position,
    const Quaternion &rotation,
    float fov,
    float aspectRatio,
    float nearPlane,
    float farPlane
)
{
    Camera camera;
    camera.position = position;
    camera.rotation = rotation;

    camera.projectionType = ProjectionType::Perspective;

    camera.perspective.fov = fov;
    camera.perspective.aspectRatio = aspectRatio;

    camera.perspective.nearPlane = nearPlane;
    camera.perspective.farPlane = farPlane;

    camera.updateViewMatrix();
    camera.updateProjectionMatrix();
    return camera;
}

Camera Camera::createOrthographic(
    const Vector3D &position,
    const Quaternion &rotation,
    float orthographicSize,
    float aspectRatio,
    float nearPlane,
    float farPlane
)
{
    Camera camera;
    camera.position = position;
    camera.rotation = rotation;

    camera.projectionType = ProjectionType::Orthographic;

    const float halfHeight = orthographicSize;
    const float halfWidth = orthographicSize * aspectRatio;

    camera.orthographic.left = -halfWidth;
    camera.orthographic.right = halfWidth;
    camera.orthographic.bottom = halfHeight;
    camera.orthographic.top = -halfHeight;

    camera.orthographic.nearPlane = nearPlane;
    camera.orthographic.farPlane = farPlane;

    camera.updateViewMatrix();
    camera.updateProjectionMatrix();
    return camera;
}

Camera Camera::createOrthographic2D(
    const Vector3D &position,
    const Quaternion &rotation,
    float width,
    float height,
    float nearPlane,
    float farPlane
)
{
    Camera camera;
    camera.position = position;
    camera.rotation = rotation;

    camera.projectionType = ProjectionType::Orthographic;

    camera.orthographic.left = 0.0f;
    camera.orthographic.right = width;
    camera.orthographic.top = 0.0f;
    camera.orthographic.bottom = height;

    camera.orthographic.nearPlane = nearPlane;
    camera.orthographic.farPlane = farPlane;

    camera.updateViewMatrix();
    camera.updateProjectionMatrix();
    return camera;
}

const Vector3D &Camera::getPosition() const
{
    return position;
}

void Camera::setPosition(const Vector3D &newPosition)
{
    position = newPosition;
    updateViewMatrix();
}

const Quaternion &Camera::getRotation() const
{
    return rotation;
}

void Camera::setRotation(const Quaternion &newRotation)
{
    rotation = newRotation.normalized();
    updateViewMatrix();
}

ProjectionType Camera::getProjectionType() const
{
    return projectionType;
}

void Camera::setProjectionType(ProjectionType newProjectionType)
{
    projectionType = newProjectionType;
    updateProjectionMatrix();
}

float Camera::getFieldOfView() const
{
    return perspective.fov;
}

void Camera::setFieldOfView(float newFov)
{
    perspective.fov = newFov;
    updateProjectionMatrix();
}

float Camera::getAspectRatio() const
{
    return perspective.aspectRatio;
}

void Camera::setAspectRatio(float newAspectRatio)
{
    perspective.aspectRatio = newAspectRatio;
    updateProjectionMatrix();
}

float Camera::getNearPlane() const
{
    switch (projectionType)
    {
    case ProjectionType::Perspective:
        return perspective.nearPlane;
    case ProjectionType::Orthographic:
        return orthographic.nearPlane;
    }
    return 0.0f;
}

void Camera::setNearPlane(float newNearPlane)
{
    switch (projectionType)
    {
    case ProjectionType::Perspective:
        perspective.nearPlane = newNearPlane;
        break;
    case ProjectionType::Orthographic:
        orthographic.nearPlane = newNearPlane;
        break;
    }
    updateProjectionMatrix();
}

float Camera::getFarPlane() const
{
    switch (projectionType)
    {
    case ProjectionType::Perspective:
        return perspective.farPlane;
    case ProjectionType::Orthographic:
        return orthographic.farPlane;
    }
    return 0.0f;
}

void Camera::setFarPlane(float newFarPlane)
{
    switch (projectionType)
    {
    case ProjectionType::Perspective:
        perspective.farPlane = newFarPlane;
        break;
    case ProjectionType::Orthographic:
        orthographic.farPlane = newFarPlane;
        break;
    }
    updateProjectionMatrix();
}

float Camera::getOrthographicLeft() const
{
    return orthographic.left;
}

void Camera::setOrthographicLeft(float newOrthographicLeft)
{
    orthographic.left = newOrthographicLeft;
    updateProjectionMatrix();
}

float Camera::getOrthographicRight() const
{
    return orthographic.right;
}

void Camera::setOrthographicRight(float newOrthographicRight)
{
    orthographic.right = newOrthographicRight;
    updateProjectionMatrix();
}

float Camera::getOrthographicBottom() const
{
    return orthographic.bottom;
}

void Camera::setOrthographicBottom(float newOrthographicBottom)
{
    orthographic.bottom = newOrthographicBottom;
    updateProjectionMatrix();
}

float Camera::getOrthographicTop() const
{
    return orthographic.top;
}

void Camera::setOrthographicTop(float newOrthographicTop)
{
    orthographic.top = newOrthographicTop;
    updateProjectionMatrix();
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

const Matrix4 &Camera::getViewMatrix() const
{
    return viewMatrix;
}

const Matrix4 &Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

void Camera::updateViewMatrix()
{
    const Quaternion inverseRotation = rotation.conjugate();

    const Matrix4 rotation = Matrix4::rotation(inverseRotation);
    const Matrix4 translation = Matrix4::translation(-position);

    viewMatrix = rotation * translation;
}

void Camera::updateProjectionMatrix()
{
    switch (projectionType)
    {
    case ProjectionType::Perspective:
    {
        projectionMatrix = Matrix4::perspective(
            perspective.fov, perspective.aspectRatio, perspective.nearPlane, perspective.farPlane
        );
        break;
    }
    case ProjectionType::Orthographic:
    {
        projectionMatrix = Matrix4::orthographic(
            orthographic.left,
            orthographic.right,
            orthographic.bottom,
            orthographic.top,
            orthographic.nearPlane,
            orthographic.farPlane
        );
        break;
    }
    default:
        LOG_ERROR("Unknown Projection Type...");
        break;
    }
}
