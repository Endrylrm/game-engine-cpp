#include "engine/core/math/Vector3DInt.hpp"

Vector3DInt Vector3DInt::Zero()
{
    return Vector3DInt{0, 0, 0};
}

Vector3DInt Vector3DInt::One()
{
    return Vector3DInt{1, 1, 1};
}

Vector3DInt Vector3DInt::Up()
{
    return Vector3DInt{0, -1, 0};
}

Vector3DInt Vector3DInt::Down()
{
    return Vector3DInt{0, 1, 0};
}

Vector3DInt Vector3DInt::Left()
{
    return Vector3DInt{-1, 0, 0};
}

Vector3DInt Vector3DInt::Right()
{
    return Vector3DInt{1, 0, 0};
}

Vector3DInt Vector3DInt::Forward()
{
    return Vector3DInt{0, 0, 1};
}

Vector3DInt Vector3DInt::Back()
{
    return Vector3DInt{0, 0, -1};
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
