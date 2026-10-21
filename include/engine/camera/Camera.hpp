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
    float aspectRatio{16.0f / 9.0f};
    float nearPlane{0.1f};
    float farPlane{100.0f};
};

struct OrthographicProjection
{
    float left{};
    float right{};
    float bottom{};
    float top{};
    float nearPlane{0.1f};
    float farPlane{100.0f};
};

class Camera
{
public:
    Camera();

    static Camera createPerspective(
        const Vector3D &position,
        const Quaternion &rotation,
        float fov,
        float aspectRatio,
        float nearPlane,
        float farPlane
    );

    static Camera createOrthographic(
        const Vector3D &position,
        const Quaternion &rotation,
        float orthographicSize,
        float aspectRatio,
        float nearPlane,
        float farPlane
    );

    static Camera createOrthographic2D(
        const Vector3D &position,
        const Quaternion &rotation,
        float width,
        float height,
        float nearPlane,
        float farPlane
    );

    const Vector3D &getPosition() const;
    void setPosition(const Vector3D &newPosition);

    const Quaternion &getRotation() const;
    void setRotation(const Quaternion &newRotation);

    ProjectionType getProjectionType() const;
    void setProjectionType(ProjectionType newProjectionType);

    float getFieldOfView() const;
    void setFieldOfView(float newFov);

    float getAspectRatio() const;
    void setAspectRatio(float newAspectRatio);

    float getNearPlane() const;
    void setNearPlane(float newNearPlane);

    float getFarPlane() const;
    void setFarPlane(float newFarPlane);

    float getOrthographicLeft() const;
    void setOrthographicLeft(float newOrthographicLeft);

    float getOrthographicRight() const;
    void setOrthographicRight(float newOrthographicRight);

    float getOrthographicBottom() const;
    void setOrthographicBottom(float newOrthographicBottom);

    float getOrthographicTop() const;
    void setOrthographicTop(float newOrthographicTop);

    Vector3D forward() const;
    Vector3D right() const;
    Vector3D up() const;

    const Matrix4 &getViewMatrix() const;
    const Matrix4 &getProjectionMatrix() const;

private:
    void updateViewMatrix();
    void updateProjectionMatrix();

    Vector3D position{};
    Quaternion rotation{Quaternion::identity()};

    ProjectionType projectionType{ProjectionType::Perspective};

    PerspectiveProjection perspective{};
    OrthographicProjection orthographic{};

    Matrix4 viewMatrix{Matrix4::identity()};
    Matrix4 projectionMatrix{Matrix4::identity()};
};
