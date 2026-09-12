#pragma once

struct Vector2DInt
{
    static Vector2DInt Zero();
    static Vector2DInt One();
    static Vector2DInt Up();
    static Vector2DInt Down();
    static Vector2DInt Left();
    static Vector2DInt Right();

    Vector2DInt operator+(const Vector2DInt &other) const;
    Vector2DInt &operator+=(const Vector2DInt &other);

    Vector2DInt operator-(const Vector2DInt &other) const;
    Vector2DInt &operator-=(const Vector2DInt &other);

    Vector2DInt operator*(int scalar) const;
    Vector2DInt &operator*=(int scalar);

    friend Vector2DInt operator*(int scalar, const Vector2DInt &vector);

    Vector2DInt operator/(int scalar) const;
    Vector2DInt &operator/=(int scalar);

    int x{};
    int y{};
};
