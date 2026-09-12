#include "engine/core/math/Vector4D.hpp"

#include <engine/core/math/Math.hpp>
#include <engine/core/math/Vector2D.hpp>
#include <engine/core/math/Vector3D.hpp>

Vector4D::Vector4D(Vector2D vec) : Vector4D(vec.x, vec.y, 0.0f, 1.0f) {}
Vector4D::Vector4D(Vector2D vec, float z, float w) : Vector4D(vec.x, vec.y, z, w) {}
Vector4D::Vector4D(Vector3D vec) : Vector4D(vec.x, vec.y, vec.z, 1.0f) {}
Vector4D::Vector4D(Vector3D vec, float w) : Vector4D(vec.x, vec.y, vec.z, w) {}

float Vector4D::length() const
{
    return std::sqrt(lengthSquared());
}

float Vector4D::lengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}

Vector4D Vector4D::normalized() const
{
    const float vectorLength = length();

    if (vectorLength == 0.0f)
        return Vector4D{};

    return *this / vectorLength;
}

void Vector4D::normalize()
{
    const float vectorLength = length();

    if (vectorLength == 0.0f)
        return;

    x /= vectorLength;
    y /= vectorLength;
    z /= vectorLength;
    w /= vectorLength;
}

float Vector4D::dot(const Vector4D &other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4D Vector4D::operator+(const Vector4D &other) const
{
    return Vector4D{x + other.x, y + other.y, z + other.z, w + other.w};
}

Vector4D &Vector4D::operator+=(const Vector4D &other)
{
    *this = *this + other;
    return *this;
}

Vector4D Vector4D::operator-(const Vector4D &other) const
{
    return Vector4D{x - other.x, y - other.y, z - other.z, w - other.w};
}

Vector4D &Vector4D::operator-=(const Vector4D &other)
{
    *this = *this - other;
    return *this;
}

Vector4D Vector4D::operator*(float scalar) const
{
    return Vector4D{x * scalar, y * scalar, z * scalar, w * scalar};
}

Vector4D &Vector4D::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector4D operator*(float scalar, const Vector4D &vector)
{
    return vector * scalar;
}

Vector4D Vector4D::operator/(float scalar) const
{
    return Vector4D{x / scalar, y / scalar, z / scalar, w / scalar};
}

Vector4D &Vector4D::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

Vector4D &Vector4D::operator=(const Vector2D &other)
{
    x = other.x;
    y = other.y;
    z = 0.0f;
    w = 1.0f;

    return *this;
}

Vector4D &Vector4D::operator=(const Vector3D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = 1.0f;

    return *this;
}

bool Vector4D::operator==(const Vector4D &other) const
{
    return Math::approximatelyEqual(x, other.x) && Math::approximatelyEqual(y, other.y) &&
           Math::approximatelyEqual(z, other.z) && Math::approximatelyEqual(w, other.w);
}

bool Vector4D::operator!=(const Vector4D &other) const
{
    return !(*this == other);
}
