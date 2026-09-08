#include "engine/core/math/Quaternion.hpp"

#include <algorithm>
#include <cmath>

#include <engine/core/math/Math.hpp>
#include <engine/core/math/conversions/GLMConverter.hpp>

constexpr Quaternion Quaternion::identity()
{
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
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

Vector3D Quaternion::rotate(const Vector3D &vector) const
{
    glm::vec3 r = GLMConverter::toGLM(*this) * glm::vec3(vector.x, vector.y, vector.z);
    return Vector3D(r.x, r.y, r.z);
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
    if (lengthSquared() < 1e-16f)
        return identity();
    return GLMConverter::fromGLM(glm::normalize(GLMConverter::toGLM(*this)));
}

void Quaternion::normalize()
{
    *this = normalized();
}

Quaternion Quaternion::conjugate() const
{
    return GLMConverter::fromGLM(glm::conjugate(GLMConverter::toGLM(*this)));
}

Quaternion Quaternion::inverse() const
{
    if (lengthSquared() < 1e-16f)
        return identity();
    return GLMConverter::fromGLM(glm::inverse(GLMConverter::toGLM(*this)));
}

float Quaternion::dot(const Quaternion &a, const Quaternion &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

void Quaternion::toAxisAngle(Vector3D &outAxis, float &outAngle) const
{
    glm::quat q =
        (std::abs(w) > 1.0f) ? GLMConverter::toGLM(normalized()) : GLMConverter::toGLM(*this);
    outAngle = glm::angle(q);
    glm::vec3 axis = glm::axis(q);
    outAxis = GLMConverter::fromGLM(axis);
}

Vector3D Quaternion::toEuler() const
{
    glm::vec3 euler = glm::eulerAngles(GLMConverter::toGLM(*this));
    return Vector3D(euler.x, euler.y, euler.z);
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
