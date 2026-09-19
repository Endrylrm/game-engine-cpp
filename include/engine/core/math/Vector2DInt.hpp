#pragma once
class Vector2D;

struct Vector2DInt
{
    static Vector2DInt zero();
    static Vector2DInt one();
    static Vector2DInt up();
    static Vector2DInt down();
    static Vector2DInt left();
    static Vector2DInt right();

    Vector2DInt operator+(const Vector2DInt &other) const;
    Vector2DInt &operator+=(const Vector2DInt &other);

    Vector2DInt operator-() const;
    Vector2DInt operator-(const Vector2DInt &other) const;
    Vector2DInt &operator-=(const Vector2DInt &other);

    Vector2DInt operator*(int scalar) const;
    Vector2DInt &operator*=(int scalar);

    friend Vector2DInt operator*(int scalar, const Vector2DInt &vector);

    Vector2DInt operator/(int scalar) const;
    Vector2DInt &operator/=(int scalar);

    operator Vector2D() const;

    int x{};
    int y{};
};
