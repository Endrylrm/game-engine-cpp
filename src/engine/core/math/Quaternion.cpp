#include "engine/core/math/Quaternion.hpp"

#include <engine/core/math/Math.hpp>
#include <engine/core/math/Matrix4.hpp>
#include <engine/core/math/Vector3D.hpp>
#include <engine/core/math/conversions/GLMConverter.hpp>

constexpr Quaternion Quaternion::identity()
{
    return Quaternion{0.0f, 0.0f, 0.0f, 1.0f};
}

Quaternion Quaternion::fromAxisAngle(const Vector3D &axis, float radians)
{
    Vector3D n = axis.normalized();
    return GLMConverter::fromGLM(glm::angleAxis(radians, GLMConverter::toGLM(n)));
}

Quaternion Quaternion::fromEuler(float pitchX, float yawY, float rollZ)
{
    return GLMConverter::fromGLM(glm::quat(glm::vec3(pitchX, yawY, rollZ)));
}

Quaternion Quaternion::fromToRotation(const Vector3D &from, const Vector3D &to)
{
    glm::vec3 f = glm::normalize(GLMConverter::toGLM(from));
    glm::vec3 t = glm::normalize(GLMConverter::toGLM(to));
    return GLMConverter::fromGLM(glm::rotation(f, t));
}

Vector3D Quaternion::rotate(const Vector3D &vector) const
{
    glm::vec3 rotation = GLMConverter::toGLM(*this) * glm::vec3(vector.x, vector.y, vector.z);
    return GLMConverter::fromGLM(rotation);
}

float Quaternion::lengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}

float Quaternion::length() const
{
    return std::sqrt(lengthSquared());
}

Quaternion Quaternion::normalized() const
{
    if (lengthSquared() < Math::EPSILON_SQUARED)
        return identity();
    return GLMConverter::fromGLM(glm::normalize(GLMConverter::toGLM(*this)));
}

void Quaternion::normalize()
{
    *this = normalized();
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion{-x, -y, -z, w};
}

Quaternion Quaternion::inverse() const
{
    const float lengthSq = lengthSquared();

    if (lengthSq < Math::EPSILON_SQUARED)
        return identity();

    return conjugate() * (1.0f / lengthSq);
}

float Quaternion::dot(const Quaternion &a, const Quaternion &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

void Quaternion::toAxisAngle(Vector3D &outAxis, float &outAngle) const
{
    const Quaternion q = normalized();
    glm::quat glmQuaternion = GLMConverter::toGLM(q);
    outAngle = glm::angle(glmQuaternion);

    const glm::vec3 axis = glm::axis(glmQuaternion);
    outAxis = GLMConverter::fromGLM(axis);
}

Vector3D Quaternion::toEuler() const
{
    const Quaternion q = normalized();
    const glm::vec3 euler = glm::eulerAngles(GLMConverter::toGLM(q));
    return {euler.x, euler.y, euler.z};
}

Quaternion Quaternion::nlerp(const Quaternion &a, const Quaternion &b, float t)
{
    const float qDot = dot(a, b);
    Quaternion bAdj = (qDot < 0.0f) ? -b : b;
    return (a * (1.0f - t) + bAdj * t).normalized();
}

Quaternion Quaternion::slerp(const Quaternion &a, const Quaternion &b, float t)
{
    return GLMConverter::fromGLM(glm::slerp(GLMConverter::toGLM(a), GLMConverter::toGLM(b), t));
}

Matrix4 Quaternion::toMatrix4() const
{
    Matrix4 result = Matrix4::identity();

    const float xx = x * x;
    const float yy = y * y;
    const float zz = z * z;

    const float xy = x * y;
    const float xz = x * z;
    const float yz = y * z;

    const float wx = w * x;
    const float wy = w * y;
    const float wz = w * z;

    result[0][0] = 1.0f - 2.0f * (yy + zz);
    result[0][1] = 2.0f * (xy - wz);
    result[0][2] = 2.0f * (xz + wy);

    result[1][0] = 2.0f * (xy + wz);
    result[1][1] = 1.0f - 2.0f * (xx + zz);
    result[1][2] = 2.0f * (yz - wx);

    result[2][0] = 2.0f * (xz - wy);
    result[2][1] = 2.0f * (yz + wx);
    result[2][2] = 1.0f - 2.0f * (xx + yy);

    return result;
}

Quaternion Quaternion::operator*(const Quaternion &other) const
{
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Quaternion &Quaternion::operator*=(const Quaternion &other)
{
    *this = (*this) * other;
    return *this;
}

Quaternion Quaternion::operator+(const Quaternion &other) const
{
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Quaternion Quaternion::operator-(const Quaternion &other) const
{
    return {x - other.x, y - other.y, z - other.z, w - other.w};
}

Quaternion Quaternion::operator*(float scalar) const
{
    return {x * scalar, y * scalar, z * scalar, w * scalar};
}

Quaternion Quaternion::operator-() const
{
    return {-x, -y, -z, -w};
}

bool Quaternion::operator==(const Quaternion &other) const
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}
