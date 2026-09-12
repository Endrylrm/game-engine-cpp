#pragma once

struct Vector3DInt
{
    static Vector3DInt Zero();
    static Vector3DInt One();
    static Vector3DInt Up();
    static Vector3DInt Down();
    static Vector3DInt Left();
    static Vector3DInt Right();
    static Vector3DInt Forward();
    static Vector3DInt Back();

    Vector3DInt operator+(const Vector3DInt &other) const;
    Vector3DInt &operator+=(const Vector3DInt &other);

    Vector3DInt operator-(const Vector3DInt &other) const;
    Vector3DInt &operator-=(const Vector3DInt &other);

    Vector3DInt operator*(int scalar) const;
    Vector3DInt &operator*=(int scalar);

    friend Vector3DInt operator*(int scalar, const Vector3DInt &vector);

    Vector3DInt operator*(const Vector3DInt &other) const;
    Vector3DInt &operator*=(const Vector3DInt &other);

    Vector3DInt operator/(int scalar) const;
    Vector3DInt &operator/=(int scalar);

    int x{};
    int y{};
    int z{};
};
