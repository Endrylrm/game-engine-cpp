#pragma once
#include <cmath>
#include <algorithm>
#include "engine/core/math/Math.hpp"
#include "engine/core/math/Vector3D.hpp"

class Quaternion
{
public:
    float x{};
    float y{};
    float z{};
    float w{1.0f};

    constexpr Quaternion() = default;
    constexpr Quaternion(float all) : x(all), y(all), z(all), w(all) {}
    constexpr Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    glm::quat toGLM() const { return glm::quat(w, x, y, z); }
    static Quaternion fromGLM(const glm::quat &q) { return Quaternion(q.x, q.y, q.z, q.w); }

    static constexpr Quaternion identity()
    {
        return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
    }

    static Quaternion fromAxisAngle(const Vector3D &axis, float radians)
    {
        Vector3D n = axis.normalized();
        return fromGLM(glm::angleAxis(radians, glm::vec3(n.x, n.y, n.z)));
    }

    static Quaternion fromEuler(float pitchX, float yawY, float rollZ)
    {
        return fromGLM(glm::quat(glm::vec3(pitchX, yawY, rollZ)));
    }

    static Quaternion fromToRotation(const Vector3D &from, const Vector3D &to)
    {
        glm::vec3 f = glm::normalize(glm::vec3(from.x, from.y, from.z));
        glm::vec3 t = glm::normalize(glm::vec3(to.x, to.y, to.z));
        return fromGLM(glm::rotation(f, t));
    }

    Quaternion operator*(const Quaternion &other) const
    {
        return Quaternion(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w,
            w * other.w - x * other.x - y * other.y - z * other.z);
    }

    Quaternion &operator*=(const Quaternion &other)
    {
        *this = (*this) * other;
        return *this;
    }

    Quaternion operator+(const Quaternion &other) const
    {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    Quaternion operator-(const Quaternion &other) const
    {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    Quaternion operator*(float scalar) const
    {
        return {x * scalar, y * scalar, z * scalar, w * scalar};
    }

    Quaternion operator-() const
    {
        return {-x, -y, -z, -w};
    }

    bool operator==(const Quaternion &other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    Vector3D rotate(const Vector3D &vector) const
    {
        glm::vec3 r = toGLM() * glm::vec3(vector.x, vector.y, vector.z);
        return Vector3D(r.x, r.y, r.z);
    }

    float lengthSquared() const
    {
        return x * x + y * y + z * z + w * w;
    }

    float length() const
    {
        return std::sqrt(lengthSquared());
    }

    Quaternion normalized() const
    {
        if (lengthSquared() < 1e-16f)
            return identity();
        return fromGLM(glm::normalize(toGLM()));
    }

    void normalize()
    {
        *this = normalized();
    }

    Quaternion conjugate() const
    {
        return fromGLM(glm::conjugate(toGLM()));
    }

    Quaternion inverse() const
    {
        if (lengthSquared() < 1e-16f)
            return identity();
        return fromGLM(glm::inverse(toGLM()));
    }

    static float dot(const Quaternion &a, const Quaternion &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    void toAxisAngle(Vector3D &outAxis, float &outAngle) const
    {
        glm::quat q = (std::abs(w) > 1.0f) ? normalized().toGLM() : toGLM();
        outAngle = glm::angle(q);
        glm::vec3 a = glm::axis(q);
        outAxis = Vector3D(a.x, a.y, a.z);
    }

    Vector3D toEuler() const
    {
        glm::vec3 e = glm::eulerAngles(toGLM());
        return Vector3D(e.x, e.y, e.z);
    }

    static Quaternion nlerp(const Quaternion &a, const Quaternion &b, float t)
    {
        const float qDot = dot(a, b);
        Quaternion bAdj = (qDot < 0.0f) ? -b : b;
        return (a * (1.0f - t) + bAdj * t).normalized();
    }

    static Quaternion slerp(const Quaternion &a, const Quaternion &b, float t)
    {
        return fromGLM(glm::slerp(a.toGLM(), b.toGLM(), t));
    }
};
