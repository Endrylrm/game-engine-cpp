#pragma once
class Vector3D;

struct Vector3DInt
{
    static Vector3DInt zero();
    static Vector3DInt one();
    static Vector3DInt up();
    static Vector3DInt down();
    static Vector3DInt left();
    static Vector3DInt right();
    static Vector3DInt forward();
    static Vector3DInt back();

    Vector3DInt operator+(const Vector3DInt &other) const;
    Vector3DInt &operator+=(const Vector3DInt &other);

    Vector3DInt operator-() const;
    Vector3DInt operator-(const Vector3DInt &other) const;
    Vector3DInt &operator-=(const Vector3DInt &other);

    Vector3DInt operator*(int scalar) const;
    Vector3DInt &operator*=(int scalar);

    friend Vector3DInt operator*(int scalar, const Vector3DInt &vector);

    Vector3DInt operator*(const Vector3DInt &other) const;
    Vector3DInt &operator*=(const Vector3DInt &other);

    Vector3DInt operator/(int scalar) const;
    Vector3DInt &operator/=(int scalar);

    operator Vector3D() const;

    int x{};
    int y{};
    int z{};
};
