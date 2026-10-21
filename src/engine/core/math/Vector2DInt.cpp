#include "engine/core/math/Vector2DInt.hpp"

#include "engine/core/math/Vector2D.hpp"

Vector2DInt Vector2DInt::zero()
{
    return Vector2DInt{0, 0};
}

Vector2DInt Vector2DInt::one()
{
    return Vector2DInt{1, 1};
}

Vector2DInt Vector2DInt::up()
{
    return Vector2DInt{0, -1};
}

Vector2DInt Vector2DInt::down()
{
    return Vector2DInt{0, 1};
}

Vector2DInt Vector2DInt::left()
{
    return Vector2DInt{-1, 0};
}

Vector2DInt Vector2DInt::right()
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

Vector2DInt Vector2DInt::operator-() const
{
    return Vector2DInt{-x, -y};
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

Vector2DInt::operator Vector2D() const
{
    return Vector2D{static_cast<float>(x), static_cast<float>(y)};
}
