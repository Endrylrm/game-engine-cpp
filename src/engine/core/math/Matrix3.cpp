#include "engine/core/math/Matrix3.hpp"

#include <engine/core/math/Math.hpp>

Matrix3::Matrix3(float diagonal) : data{}
{
    data[0][0] = diagonal;
    data[1][1] = diagonal;
    data[2][2] = diagonal;
}

// Matrix operations
Matrix3 Matrix3::identity()
{
    return Matrix3(1.0f);
}

float Matrix3::determinant() const
{
    const float a = data[0][0];
    const float b = data[0][1];
    const float c = data[0][2];

    const float d = data[1][0];
    const float e = data[1][1];
    const float f = data[1][2];

    const float g = data[2][0];
    const float h = data[2][1];
    const float i = data[2][2];

    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

Matrix3 Matrix3::inverse() const
{
    const float det = determinant();

    if (std::abs(det) < Math::EPSILON)
    {
        return Matrix3::identity();
    }

    const float invDet = 1.0f / det;

    Matrix3 result;

    result[0][0] = (data[1][1] * data[2][2] - data[1][2] * data[2][1]) * invDet;
    result[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) * invDet;
    result[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * invDet;

    result[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) * invDet;
    result[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * invDet;
    result[1][2] = (data[0][2] * data[1][0] - data[0][0] * data[1][2]) * invDet;

    result[2][0] = (data[1][0] * data[2][1] - data[1][1] * data[2][0]) * invDet;
    result[2][1] = (data[0][1] * data[2][0] - data[0][0] * data[2][1]) * invDet;
    result[2][2] = (data[0][0] * data[1][1] - data[0][1] * data[1][0]) * invDet;

    return result;
}

bool Matrix3::tryInverse(Matrix3 &result) const
{
    const float det = determinant();

    if (std::abs(det) < Math::EPSILON)
        return false;

    const float invDet = 1.0f / det;

    result[0][0] = (data[1][1] * data[2][2] - data[1][2] * data[2][1]) * invDet;
    result[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) * invDet;
    result[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * invDet;

    result[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) * invDet;
    result[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * invDet;
    result[1][2] = (data[0][2] * data[1][0] - data[0][0] * data[1][2]) * invDet;

    result[2][0] = (data[1][0] * data[2][1] - data[1][1] * data[2][0]) * invDet;
    result[2][1] = (data[0][1] * data[2][0] - data[0][0] * data[2][1]) * invDet;
    result[2][2] = (data[0][0] * data[1][1] - data[0][1] * data[1][0]) * invDet;

    return true;
}

Matrix3 Matrix3::transpose() const
{
    Matrix3 result;

    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t column = 0; column < 3; ++column)
        {
            result[row][column] = data[column][row];
        }
    }

    return result;
}

// Transformations
Matrix3 Matrix3::translation(const Vector2D &position)
{
    Matrix3 result = Matrix3::identity();

    result[0][2] = position.x;
    result[1][2] = position.y;

    return result;
}

Matrix3 Matrix3::rotation(float angle)
{
    Matrix3 result = Matrix3::identity();

    const float c = std::cos(angle);
    const float s = std::sin(angle);

    result[0][0] = c;
    result[0][1] = -s;
    result[1][0] = s;
    result[1][1] = c;

    return result;
}

Matrix3 Matrix3::rotation(const Quaternion &quat)
{
    Quaternion n = quat.normalized();

    Matrix3 result(1.0f);

    const float xx = n.x * n.x;
    const float yy = n.y * n.y;
    const float zz = n.z * n.z;

    const float xy = n.x * n.y;
    const float xz = n.x * n.z;
    const float yz = n.y * n.z;

    const float wx = n.w * n.x;
    const float wy = n.w * n.y;
    const float wz = n.w * n.z;

    result[0][0] = 1.0f - 2.0f * (yy + zz);
    result[0][1] = 2.0f * (xy - wz);
    result[0][2] = 2.0f * (xz + wy);

    result[1][0] = 2.0f * (xy + wz);
    result[1][1] = 1.0f - 2.0f * (xx + zz);
    result[1][2] = 2.0f * (yz - wx);

    result[2][0] = 2.0f * (xz - wy);
    result[2][1] = 2.0f * (yz + wx);
    result[2][2] = 1.0f - 2.0f * (xx + yy);

    return result;
}

Matrix3 Matrix3::scale(const Vector2D &scale)
{
    Matrix3 result = Matrix3::identity();

    result[0][0] = scale.x;
    result[1][1] = scale.y;

    return result;
}

Vector2D Matrix3::transformPoint(const Vector2D &point) const
{
    return Vector2D(
        data[0][0] * point.x + data[0][1] * point.y + data[0][2],
        data[1][0] * point.x + data[1][1] * point.y + data[1][2]
    );
}

Vector2D Matrix3::transformDirection(const Vector2D &direction) const
{
    return Vector2D(
        data[0][0] * direction.x + data[0][1] * direction.y,
        data[1][0] * direction.x + data[1][1] * direction.y
    );
}

// Operators
Matrix3 Matrix3::operator+(const Matrix3 &other) const
{
    Matrix3 result;

    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t column = 0; column < 3; ++column)
        {
            result[row][column] = data[row][column] + other[row][column];
        }
    }

    return result;
}

Matrix3 &Matrix3::operator+=(const Matrix3 &other)
{
    *this = *this + other;
    return *this;
}

Matrix3 Matrix3::operator-(const Matrix3 &other) const
{
    Matrix3 result;

    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t column = 0; column < 3; ++column)
        {
            result[row][column] = data[row][column] - other[row][column];
        }
    }

    return result;
}

Matrix3 &Matrix3::operator-=(const Matrix3 &other)
{
    *this = *this - other;
    return *this;
}

Matrix3 Matrix3::operator*(const Matrix3 &other) const
{
    Matrix3 result;

    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t column = 0; column < 3; ++column)
        {
            result[row][column] = 0.0f;

            for (size_t k = 0; k < 3; ++k)
            {
                result[row][column] += data[row][k] * other[k][column];
            }
        }
    }

    return result;
}

Matrix3 &Matrix3::operator*=(const Matrix3 &other)
{
    *this = *this * other;
    return *this;
}

Matrix3 Matrix3::operator*(float scalar) const
{
    Matrix3 result;

    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t column = 0; column < 3; ++column)
        {
            result[row][column] = data[row][column] * scalar;
        }
    }

    return result;
}

Matrix3 &Matrix3::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector3D Matrix3::operator*(const Vector3D &vector) const
{
    return Vector3D(
        data[0][0] * vector.x + data[0][1] * vector.y + data[0][2] * vector.z,
        data[1][0] * vector.x + data[1][1] * vector.y + data[1][2] * vector.z,
        data[2][0] * vector.x + data[2][1] * vector.y + data[2][2] * vector.z
    );
}

bool Matrix3::operator==(const Matrix3 &other) const
{
    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t column = 0; column < 3; ++column)
        {
            if (!Math::approximatelyEqual(data[row][column], other[row][column]))
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix3::operator!=(const Matrix3 &other) const
{
    return !(*this == other);
}

float *Matrix3::operator[](size_t row)
{
    return data[row];
}

const float *Matrix3::operator[](size_t row) const
{
    return data[row];
}
