#include "engine/core/math/Vector2DInt.hpp"

Vector2DInt Vector2DInt::Zero()
{
    return Vector2DInt{0, 0};
}

Vector2DInt Vector2DInt::One()
{
    return Vector2DInt{1, 1};
}

Vector2DInt Vector2DInt::Up()
{
    return Vector2DInt{0, -1};
}

Vector2DInt Vector2DInt::Down()
{
    return Vector2DInt{0, 1};
}

Vector2DInt Vector2DInt::Left()
{
    return Vector2DInt{-1, 0};
}

Vector2DInt Vector2DInt::Right()
{
    return Vector2DInt{1, 0};
}

Vector2DInt Vector2DInt::operator+(const Vector2DInt &other) const
{
    return Vector2DInt{x + other.x, y + other.y};
}

Vector2DInt &Vector2DInt::operator+=(const Vector2DInt &other)
{
    *this = *this + other;
    return *this;
}

Vector2DInt Vector2DInt::operator-(const Vector2DInt &other) const
{
    return Vector2DInt{x - other.x, y - other.y};
}

Vector2DInt &Vector2DInt::operator-=(const Vector2DInt &other)
{
    *this = *this - other;
    return *this;
}

Vector2DInt Vector2DInt::operator*(int scalar) const
{
    return Vector2DInt{x * scalar, y * scalar};
}

Vector2DInt &Vector2DInt::operator*=(int scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector2DInt operator*(int scalar, const Vector2DInt &vector)
{
    return vector * scalar;
}

Vector2DInt Vector2DInt::operator/(int scalar) const
{
    return Vector2DInt{x / scalar, y / scalar};
}

Vector2DInt &Vector2DInt::operator/=(int scalar)
{
    *this = *this / scalar;
    return *this;
}
