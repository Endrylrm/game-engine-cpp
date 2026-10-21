#include "engine/core/math/Vector3DInt.hpp"

#include "engine/core/math/Vector3D.hpp"

Vector3DInt Vector3DInt::zero()
{
    return Vector3DInt{0, 0, 0};
}

Vector3DInt Vector3DInt::one()
{
    return Vector3DInt{1, 1, 1};
}

Vector3DInt Vector3DInt::up()
{
    return Vector3DInt{0, -1, 0};
}

Vector3DInt Vector3DInt::down()
{
    return Vector3DInt{0, 1, 0};
}

Vector3DInt Vector3DInt::left()
{
    return Vector3DInt{-1, 0, 0};
}

Vector3DInt Vector3DInt::right()
{
    return Vector3DInt{1, 0, 0};
}

Vector3DInt Vector3DInt::forward()
{
    return Vector3DInt{0, 0, -1};
}

Vector3DInt Vector3DInt::back()
{
    return Vector3DInt{0, 0, 1};
}

Vector3DInt Vector3DInt::operator+(const Vector3DInt &other) const
{
    return Vector3DInt{x + other.x, y + other.y, z + other.z};
}

Vector3DInt &Vector3DInt::operator+=(const Vector3DInt &other)
{
    *this = *this + other;
    return *this;
}

Vector3DInt Vector3DInt::operator-() const
{
    return Vector3DInt{-x, -y, -z};
}

Vector3DInt Vector3DInt::operator-(const Vector3DInt &other) const
{
    return Vector3DInt{x - other.x, y - other.y, z - other.z};
}

Vector3DInt &Vector3DInt::operator-=(const Vector3DInt &other)
{
    *this = *this - other;
    return *this;
}

Vector3DInt Vector3DInt::operator*(int scalar) const
{
    return Vector3DInt{x * scalar, y * scalar, z * scalar};
}

Vector3DInt &Vector3DInt::operator*=(int scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector3DInt operator*(int scalar, const Vector3DInt &vector)
{
    return vector * scalar;
}

Vector3DInt Vector3DInt::operator*(const Vector3DInt &other) const
{
    return Vector3DInt{x * other.x, y * other.y, z * other.z};
}

Vector3DInt &Vector3DInt::operator*=(const Vector3DInt &other)
{
    *this = *this * other;
    return *this;
}

Vector3DInt Vector3DInt::operator/(int scalar) const
{
    return Vector3DInt{x / scalar, y / scalar, z / scalar};
}

Vector3DInt &Vector3DInt::operator/=(int scalar)
{
    *this = *this / scalar;
    return *this;
}

Vector3DInt::operator Vector3D() const
{
    return Vector3D{static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
}
