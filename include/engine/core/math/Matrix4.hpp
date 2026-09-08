#pragma once
#include <cstdint>

#include "Vector3D.hpp"
#include "Vector4D.hpp"

class Matrix4
{
public:
    // Construction
    Matrix4() = default;
    explicit Matrix4(float diagonal);

    static Matrix4 identity();

    // Matrix operations
    float determinant() const;
    Matrix4 inverse() const;
    bool tryInverse(Matrix4 &result) const;
    Matrix4 transpose() const;

    // Transformations
    static Matrix4 translation(const Vector3D &position);
    static Matrix4 rotation(float angle, const Vector3D &axis);
    static Matrix4 rotationX(float angle);
    static Matrix4 rotationY(float angle);
    static Matrix4 rotationZ(float angle);
    static Matrix4 scale(const Vector3D &scale);

    Vector3D transformPoint(const Vector3D &point) const;
    Vector3D transformDirection(const Vector3D &direction) const;

    // Projection
    static Matrix4
    orthographic(float left, float right, float bottom, float top, float near, float far);
    static Matrix4 perspective(float fov, float aspect, float near, float far);
    static Matrix4 lookAt(const Vector3D &eye, const Vector3D &target, const Vector3D &up);

    // Operators
    Matrix4 operator+(const Matrix4 &other) const;
    Matrix4 &operator+=(const Matrix4 &other);

    Matrix4 operator-(const Matrix4 &other) const;
    Matrix4 &operator-=(const Matrix4 &other);

    Matrix4 operator*(const Matrix4 &other) const;
    Matrix4 &operator*=(const Matrix4 &other);

    Matrix4 operator*(float scalar) const;
    Matrix4 &operator*=(float scalar);

    Vector4D operator*(const Vector4D &vector) const;

    bool operator==(const Matrix4 &other) const;

    float *operator[](size_t row);
    const float *operator[](size_t row) const;

private:
    float data[4][4]{};
};
