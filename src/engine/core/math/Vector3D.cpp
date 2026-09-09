#include "engine/core/math/Vector3D.hpp"

#include <engine/core/math/Math.hpp>
#include <engine/core/math/Vector2D.hpp>
#include <engine/core/math/Vector4D.hpp>

Vector3D::Vector3D(Vector2D vec) : x(vec.x), y(vec.y), z(0.0f) {}
Vector3D::Vector3D(Vector4D vec) : x(vec.x), y(vec.y), z(vec.z) {}

Vector3D Vector3D::Zero()
{
    return Vector3D{0.0f, 0.0f, 0.0f};
}

Vector3D Vector3D::One()
{
    return Vector3D{1.0f, 1.0f, 1.0f};
}

Vector3D Vector3D::Up()
{
    return {0.0f, -1.0f, 0.0f};
}

Vector3D Vector3D::Down()
{
    return {0.0f, 1.0f, 0.0f};
}

Vector3D Vector3D::Left()
{
    return {-1.0f, 0.0f, 0.0f};
}

Vector3D Vector3D::Right()
{
    return {1.0f, 0.0f, 0.0f};
}

Vector3D Vector3D::Forward()
{
    return {0.0f, 0.0f, 1.0f};
}

Vector3D Vector3D::Back()
{
    return {0.0f, 0.0f, -1.0f};
}

bool Vector3D::isZero() const
{
    return lengthSquared() < Math::EPSILON;
}

float Vector3D::length() const
{
    float vectorLength = std::hypot(std::hypot(x, y), z);
    return vectorLength;
}

float Vector3D::lengthSquared() const
{
    return x * x + y * y + z * z;
}

void Vector3D::normalize()
{
    float vectorLength = length();

    if (vectorLength > 0.0f)
    {
        x /= vectorLength;
        y /= vectorLength;
        z /= vectorLength;
    }
}

Vector3D Vector3D::normalized() const
{
    float vectorLength = length();

    if (vectorLength < Math::EPSILON)
        return {0.0f, 0.0f, 0.0f};

    return {x / vectorLength, y / vectorLength, z / vectorLength};
}

float Vector3D::distance(const Vector3D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;
    float dz = other.z - z;

    return std::hypot(std::hypot(dx, dy), dz);
}

float Vector3D::distanceSquared(const Vector3D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;
    float dz = other.z - z;

    return dx * dx + dy * dy + dz * dz;
}

float Vector3D::dot(const Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return Vector3D(
        y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x
    );
}

float Vector3D::angle(const Vector3D &other) const
{
    float lengths = length() * other.length();

    if (lengths <= Math::EPSILON)
        return 0.0f;

    float cosine = dot(other) / lengths;
    cosine = std::clamp(cosine, -1.0f, 1.0f);
    return std::acos(cosine);
}

float Vector3D::angleDegrees(const Vector3D &other) const
{
    return angle(other) * 180.0f / Math::PI;
}

float Vector3D::pitch() const
{
    return std::atan2(y, std::hypot(x * x, z * z));
}

float Vector3D::pitchDegrees() const
{
    return std::atan2(z, std::hypot(x * x, y * y)) * 180.0f / Math::PI;
}

float Vector3D::yaw() const
{
    return std::atan2(x, z);
}

float Vector3D::yawDegrees() const
{
    return std::atan2(y, x) * 180.0f / Math::PI;
}

Vector3D Vector3D::moveTowards(const Vector3D &target, float maxDistanceDelta) const
{
    Vector3D delta = target - *this;

    float distance = delta.length();

    if (distance <= maxDistanceDelta || distance < Math::EPSILON)
        return target;

    return *this + delta / distance * maxDistanceDelta;
}

Vector3D Vector3D::rotateTowards(const Vector3D &target, float maxRadiansDelta) const
{
    Vector3D from = normalized();
    Vector3D to = target.normalized();

    float dotProduct = from.dot(to);

    dotProduct = std::clamp(dotProduct, -1.0f, 1.0f);

    float angle = std::acos(dotProduct);

    if (angle < Math::EPSILON)
        return target;

    float t = std::min(1.0f, maxRadiansDelta / angle);

    float sinAngle = std::sin(angle);

    float a = std::sin((1.0f - t) * angle) / sinAngle;
    float b = std::sin(t * angle) / sinAngle;

    return (from * a + to * b);
}

Vector3D Vector3D::lerp(const Vector3D &target, float t) const
{
    return {x + (target.x - x) * t, y + (target.y - y) * t, z + (target.z - z) * t};
}

Vector3D Vector3D::project(const Vector3D &onto) const
{
    float lengthSq = onto.lengthSquared();

    if (lengthSq == 0.0f)
        return Vector3D(0.0f);

    return onto * (dot(onto) / lengthSq);
}

Vector3D Vector3D::reflect(const Vector3D &normal) const
{
    return *this - normal * (2.0f * dot(normal));
}

Vector3D Vector3D::clampMagnitude(float maxLength) const
{
    float vectorLength = length();

    if (vectorLength <= maxLength)
        return *this;

    return normalized() * maxLength;
}

Vector3D Vector3D::perpendicular() const
{
    if (std::abs(x) < std::abs(y))
        return cross(Vector3D(1, 0, 0)).normalized();

    return cross(Vector3D(0, 1, 0)).normalized();
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D{x + other.x, y + other.y, z + other.z};
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    *this = *this + other;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D{x - other.x, y - other.y, z - other.z};
}

Vector3D &Vector3D::operator-=(const Vector3D &other)
{
    *this = *this - other;
    return *this;
}

Vector3D Vector3D::operator*(float scalar) const
{
    return Vector3D{x * scalar, y * scalar, z * scalar};
}

Vector3D &Vector3D::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector3D operator*(float scalar, const Vector3D &vector)
{
    return vector * scalar;
}

Vector3D Vector3D::operator*(const Vector3D &other) const
{
    return Vector3D{x * other.x, y * other.y, z * other.z};
}

Vector3D &Vector3D::operator*=(const Vector3D &other)
{
    *this = *this * other;
    return *this;
}

Vector3D Vector3D::operator/(float scalar) const
{
    return Vector3D{x / scalar, y / scalar, z / scalar};
}

Vector3D &Vector3D::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

Vector3D &Vector3D::operator=(const Vector2D &other)
{
    x = other.x;
    y = other.y;
    z = 0.0f;

    return *this;
}

Vector3D &Vector3D::operator=(const Vector4D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

bool Vector3D::operator==(const Vector3D &other) const
{
    return Math::approximatelyEqual(x, other.x) && Math::approximatelyEqual(y, other.y) &&
           Math::approximatelyEqual(z, other.z);
}

bool Vector3D::operator!=(const Vector3D &other) const
{
    return !(*this == other);
}
