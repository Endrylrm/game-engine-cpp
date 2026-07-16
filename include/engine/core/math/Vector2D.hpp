#pragma once
#include <cmath>
#include <numbers>
#include "engine/core/math/Math.hpp"

class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(float all) : x(all), y(all) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    float x = 0.0f;
    float y = 0.0f;

    glm::vec2 toGLM() const
    {
        return {x, y};
    }

    static Vector2D fromGLM(const glm::vec2 &glmVector)
    {
        return {glmVector.x, glmVector.y};
    }

    static Vector2D Zero()
    {
        return Vector2D{0.0f, 0.0f};
    }

    static Vector2D One()
    {
        return Vector2D{1.0f, 1.0f};
    }

    static Vector2D Up()
    {
        return {0.0f, 1.0f};
    }

    static Vector2D Down()
    {
        return {0.0f, -1.0f};
    }

    static Vector2D Left()
    {
        return {-1.0f, 0.0f};
    }

    static Vector2D Right()
    {
        return {1.0f, 0.0f};
    }

    float length() const
    {
        float vectorLength = std::hypot(x, y);
        return vectorLength;
    }

    float lengthSquared() const
    {
        return x * x + y * y;
    }

    void normalize()
    {
        float vectorLength = length();

        if (vectorLength > 0.0f)
        {
            x /= vectorLength;
            y /= vectorLength;
        }
    }

    Vector2D normalized() const
    {
        return Vector2D::fromGLM(glm::normalize(toGLM()));
    }

    float distance(const Vector2D &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;

        return std::sqrt(dx * dx + dy * dy);
    }

    float distanceSquared(const Vector2D &other) const
    {
        float dx = other.x - x;
        float dy = other.y - y;

        return dx * dx + dy * dy;
    }

    float dot(const Vector2D &other) const
    {
        return x * other.x + y * other.y;
    }

    float cross(const Vector2D &other) const
    {
        return x * other.y - y * other.x;
    }

    float angle() const
    {
        return std::atan2(y, x);
    }

    float angleDegrees() const
    {
        return std::atan2(y, x) * 180.0f / std::numbers::pi_v<float>;
    }

    float angleTo(const Vector2D &other) const
    {
        return std::atan2(cross(other), dot(other));
    }

    Vector2D MoveTowards(const Vector2D &target, float maxDistanceDelta) const
    {
        Vector2D delta = target - *this;

        float distance = delta.length();

        if (distance <= maxDistanceDelta || distance == 0.0f)
            return target;

        return *this + delta / distance * maxDistanceDelta;
    }

    Vector2D rotate(float radians) const
    {
        float c = std::cos(radians);
        float s = std::sin(radians);

        return {x * c - y * s, x * s + y * c};
    }

    Vector2D lerp(const Vector2D &target, float t) const
    {
        return {x + (target.x - x) * t, y + (target.y - y) * t};
    }

    Vector2D project(const Vector2D &onto) const
    {
        float lengthSq = onto.lengthSquared();

        if (lengthSq == 0.0f)
            return Vector2D(0.0f, 0.0f);

        return onto * (dot(onto) / lengthSq);
    }

    Vector2D reflect(const Vector2D &normal) const
    {
        return *this - normal * (2.0f * dot(normal));
    }

    Vector2D clampMagnitude(float maxLength) const
    {
        float vectorLength = length();

        if (vectorLength <= maxLength)
            return *this;

        return normalized() * maxLength;
    }

    Vector2D perpendicularLeft() const
    {
        return {-y, x};
    }

    Vector2D perpendicularRight() const
    {
        return {y, -x};
    }

    Vector2D &operator+=(const Vector2D &other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector2D operator+(const Vector2D &other) const
    {
        Vector2D result = *this;
        result += other;
        return result;
    }

    Vector2D &operator-=(const Vector2D &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vector2D operator-(const Vector2D &other) const
    {
        Vector2D result = *this;
        result -= other;
        return result;
    }

    Vector2D &operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vector2D operator*(float scalar) const
    {
        Vector2D result = *this;
        result *= scalar;
        return result;
    }

    Vector2D &operator/=(float scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    Vector2D operator/(float scalar) const
    {
        Vector2D result = *this;
        result /= scalar;
        return result;
    }
};
