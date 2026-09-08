#include "engine/core/math/Vector2D.hpp"

#include <cmath>
#include <numbers>

#include <engine/core/math/Math.hpp>
#include <engine/core/math/conversions/GLMConverter.hpp>

Vector2D Vector2D::Zero()
{
    return Vector2D{0.0f, 0.0f};
}

Vector2D Vector2D::One()
{
    return Vector2D{1.0f, 1.0f};
}

Vector2D Vector2D::Up()
{
    return {0.0f, 1.0f};
}

Vector2D Vector2D::Down()
{
    return {0.0f, -1.0f};
}

Vector2D Vector2D::Left()
{
    return {-1.0f, 0.0f};
}

Vector2D Vector2D::Right()
{
    return {1.0f, 0.0f};
}

float Vector2D::length() const
{
    float vectorLength = std::hypot(x, y);
    return vectorLength;
}

float Vector2D::lengthSquared() const
{
    return x * x + y * y;
}

void Vector2D::normalize()
{
    float vectorLength = length();

    if (vectorLength > 0.0f)
    {
        x /= vectorLength;
        y /= vectorLength;
    }
}

Vector2D Vector2D::normalized() const
{
    return GLMConverter::fromGLM(glm::normalize(GLMConverter::toGLM(*this)));
}

float Vector2D::distance(const Vector2D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;

    return std::sqrt(dx * dx + dy * dy);
}

float Vector2D::distanceSquared(const Vector2D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;

    return dx * dx + dy * dy;
}

float Vector2D::dot(const Vector2D &other) const
{
    return x * other.x + y * other.y;
}

float Vector2D::cross(const Vector2D &other) const
{
    return x * other.y - y * other.x;
}

float Vector2D::angle() const
{
    return std::atan2(y, x);
}

float Vector2D::angleDegrees() const
{
    return std::atan2(y, x) * 180.0f / std::numbers::pi_v<float>;
}

float Vector2D::angleTo(const Vector2D &other) const
{
    return std::atan2(cross(other), dot(other));
}

Vector2D Vector2D::MoveTowards(const Vector2D &target, float maxDistanceDelta) const
{
    Vector2D delta = target - *this;

    float distance = delta.length();

    if (distance <= maxDistanceDelta || distance == 0.0f)
        return target;

    return *this + delta / distance * maxDistanceDelta;
}

Vector2D Vector2D::rotate(float radians) const
{
    float c = std::cos(radians);
    float s = std::sin(radians);

    return {x * c - y * s, x * s + y * c};
}

Vector2D Vector2D::lerp(const Vector2D &target, float t) const
{
    return {x + (target.x - x) * t, y + (target.y - y) * t};
}

Vector2D Vector2D::project(const Vector2D &onto) const
{
    float lengthSq = onto.lengthSquared();

    if (lengthSq == 0.0f)
        return Vector2D(0.0f, 0.0f);

    return onto * (dot(onto) / lengthSq);
}

Vector2D Vector2D::reflect(const Vector2D &normal) const
{
    return *this - normal * (2.0f * dot(normal));
}

Vector2D Vector2D::clampMagnitude(float maxLength) const
{
    float vectorLength = length();

    if (vectorLength <= maxLength)
        return *this;

    return normalized() * maxLength;
}

Vector2D Vector2D::perpendicularLeft() const
{
    return {-y, x};
}

Vector2D Vector2D::perpendicularRight() const
{
    return {y, -x};
}

Vector2D &Vector2D::operator+=(const Vector2D &other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D &other) const
{
    Vector2D result = *this;
    result += other;
    return result;
}

Vector2D &Vector2D::operator-=(const Vector2D &other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
    Vector2D result = *this;
    result -= other;
    return result;
}

Vector2D &Vector2D::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2D Vector2D::operator*(float scalar) const
{
    Vector2D result = *this;
    result *= scalar;
    return result;
}

Vector2D &Vector2D::operator/=(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

Vector2D Vector2D::operator/(float scalar) const
{
    Vector2D result = *this;
    result /= scalar;
    return result;
}
