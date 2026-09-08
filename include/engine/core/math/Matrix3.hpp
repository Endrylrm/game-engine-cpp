#pragma once
#include <cstdint>

#include "Quaternion.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"

class Matrix3
{
public:
    // Construction
    Matrix3() = default;
    explicit Matrix3(float diagonal);

    static Matrix3 identity();

    // Matrix operations
    float determinant() const;
    Matrix3 inverse() const;
    bool tryInverse(Matrix3 &result) const;
    Matrix3 transpose() const;

    // Transformations
    Matrix3 translation(const Vector2D &position);
    static Matrix3 rotation(float angle);
    static Matrix3 rotation(const Quaternion &quat);
    static Matrix3 scale(const Vector2D &scale);

    Vector2D transformPoint(const Vector2D &point) const;
    Vector2D transformDirection(const Vector2D &direction) const;

    // Operators
    Matrix3 operator+(const Matrix3 &other) const;
    Matrix3 &operator+=(const Matrix3 &other);

    Matrix3 operator-(const Matrix3 &other) const;
    Matrix3 &operator-=(const Matrix3 &other);

    Matrix3 operator*(const Matrix3 &other) const;
    Matrix3 &operator*=(const Matrix3 &other);

    Matrix3 operator*(float scalar) const;
    Matrix3 &operator*=(float scalar);

    Vector3D operator*(const Vector3D &vector) const;

    bool operator==(const Matrix3 &other) const;
    bool operator!=(const Matrix3 &other) const;

    float *operator[](size_t row);
    const float *operator[](size_t row) const;

private:
    float data[3][3]{};
};
