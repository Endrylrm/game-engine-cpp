#pragma once
#include <cmath>
#include <numbers>
#include <algorithm>
#include "engine/core/math/Math.hpp"
#include "engine/core/math/Vector2D.hpp"

float EPSILON = 0.000001f;

class Vector3D
{
public:
    Vector3D() = default;
    Vector3D(float all) : x(all), y(all), z(all) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    static Vector3D Zero()
    {
        return Vector3D{0.0f, 0.0f, 0.0f};
    }

    static Vector3D One()
    {
        return Vector3D{1.0f, 1.0f, 1.0f};
    }

    static Vector3D Up()
    {
        return {0.0f, 1.0f, 0.0f};
    }

    static Vector3D Down()
    {
        return {0.0f, -1.0f, 0.0f};
    }

    static Vector3D Left()
    {
        return {-1.0f, 0.0f, 0.0f};
    }

    static Vector3D Right()
    {
        return {1.0f, 0.0f, 0.0f};
    }

    static Vector3D Forward()
    {
        return {0.0f, 0.0f, 1.0f};
    }

    static Vector3D Back()
    {
        return {0.0f, 0.0f, -1.0f};
    }

    bool isZero() const
    {
        return lengthSquared() < EPSILON;
    }

    float length() const
    {
        float vectorLength = std::hypot(std::hypot(x, y), z);
        return vectorLength;
    }

    float lengthSquared() const
    {
        return x * x + y * y + z * z;
    }

    void normalize()
    {
        float vectorLength = length();

        if (vectorLength > 0.0f)
        {
            x /= vectorLength;
            y /= vectorLength;
            z /= vectorLength;
        }
    }

    Vector3D normalized() const
    {
        float vectorLength = length();

        if (vectorLength < EPSILON)
            return {0.0f, 0.0f, 0.0f};

        return {x / vectorLength, y / vectorLength, z / vectorLength};
    }

    float distance(const Vector3D &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;
        float dz = other.z - z;

        return std::hypot(std::hypot(dx, dy), dz);
    }

    float distanceSquared(const Vector3D &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;
        float dz = other.z - z;

        return dx * dx + dy * dy + dz * dz;
    }

    float dot(const Vector3D &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D cross(const Vector3D &other) const
    {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    float angle(const Vector3D &other) const
    {
        float lengths = length() * other.length();

        if (lengths <= std::numeric_limits<float>::epsilon())
            return 0.0f;

        float cosine = dot(other) / lengths;
        cosine = std::clamp(cosine, -1.0f, 1.0f);
        return std::acos(cosine);
    }

    float angleDegrees(const Vector3D &other) const
    {
        return angle(other) * 180.0f / std::numbers::pi_v<float>;
    }

    float pitch() const
    {
        return std::atan2(y, std::hypot(x * x, z * z));
    }

    float pitchDegrees() const
    {
        return std::atan2(z, std::hypot(x * x, y * y)) * 180.0f / std::numbers::pi_v<float>;
    }

    float yaw() const
    {
        return std::atan2(x, z);
    }

    float yawDegrees() const
    {
        return std::atan2(y, x) * 180.0f / std::numbers::pi_v<float>;
    }

    Vector3D MoveTowards(const Vector3D &target, float maxDistanceDelta) const
    {
        Vector3D delta = target - *this;

        float distance = delta.length();

        if (distance <= maxDistanceDelta || distance < EPSILON)
            return target;

        return *this + delta / distance * maxDistanceDelta;
    }

    Vector3D rotateTowards(const Vector3D &target, float maxRadiansDelta) const
    {
        Vector3D from = normalized();
        Vector3D to = target.normalized();

        float dotProduct = from.dot(to);

        dotProduct = std::clamp(dotProduct, -1.0f, 1.0f);

        float angle = std::acos(dotProduct);

        if (angle < EPSILON)
            return target;

        float t = std::min(1.0f, maxRadiansDelta / angle);

        float sinAngle = std::sin(angle);

        float a = std::sin((1.0f - t) * angle) / sinAngle;
        float b = std::sin(t * angle) / sinAngle;

        return (from * a + to * b);
    }

    Vector3D lerp(const Vector3D &target, float t) const
    {
        return {x + (target.x - x) * t, y + (target.y - y) * t, z + (target.z - z) * t};
    }

    Vector3D project(const Vector3D &onto) const
    {
        float lengthSq = onto.lengthSquared();

        if (lengthSq == 0.0f)
            return Vector3D(0.0f);

        return onto * (dot(onto) / lengthSq);
    }

    Vector3D reflect(const Vector3D &normal) const
    {
        return *this - normal * (2.0f * dot(normal));
    }

    Vector3D clampMagnitude(float maxLength) const
    {
        float vectorLength = length();

        if (vectorLength <= maxLength)
            return *this;

        return normalized() * maxLength;
    }

    Vector3D perpendicular() const
    {
        if (std::abs(x) < std::abs(y))
            return cross(Vector3D(1, 0, 0)).normalized();

        return cross(Vector3D(0, 1, 0)).normalized();
    }

    Vector3D &operator+=(const Vector3D &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vector3D operator+(const Vector3D &other) const
    {
        Vector3D result = *this;
        result += other;
        return result;
    }

    Vector3D &operator-=(const Vector3D &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vector3D operator-(const Vector3D &other) const
    {
        Vector3D result = *this;
        result -= other;
        return result;
    }

    Vector3D &operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }

    Vector3D operator*(float scalar) const
    {
        Vector3D result = *this;
        result *= scalar;
        return result;
    }

    Vector3D &operator/=(float scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        return *this;
    }

    Vector3D operator/(float scalar) const
    {
        Vector3D result = *this;
        result /= scalar;
        return result;
    }
};
