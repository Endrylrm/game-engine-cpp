#include "engine/core/math/Matrix3.hpp"

#include "engine/core/math/Math.hpp"

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
    const float A = data[0][0];
    const float B = data[0][1];
    const float C = data[0][2];

    const float D = data[1][0];
    const float E = data[1][1];
    const float F = data[1][2];

    const float G = data[2][0];
    const float H = data[2][1];
    const float I = data[2][2];

    return A * (E * I - F * H) - B * (D * I - F * G) + C * (D * H - E * G);
}

Matrix3 Matrix3::inverse() const
{
    const float DET = determinant();

    if (std::abs(DET) < Math::EPSILON)
    {
        return Matrix3::identity();
    }

    const float INV_DET = 1.0f / DET;

    Matrix3 result;

    result[0][0] = (data[1][1] * data[2][2] - data[1][2] * data[2][1]) * INV_DET;
    result[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) * INV_DET;
    result[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * INV_DET;

    result[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) * INV_DET;
    result[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * INV_DET;
    result[1][2] = (data[0][2] * data[1][0] - data[0][0] * data[1][2]) * INV_DET;

    result[2][0] = (data[1][0] * data[2][1] - data[1][1] * data[2][0]) * INV_DET;
    result[2][1] = (data[0][1] * data[2][0] - data[0][0] * data[2][1]) * INV_DET;
    result[2][2] = (data[0][0] * data[1][1] - data[0][1] * data[1][0]) * INV_DET;

    return result;
}

bool Matrix3::try_inverse(Matrix3 &result) const
{
    const float DET = determinant();

    if (std::abs(DET) < Math::EPSILON)
        return false;

    const float INV_DET = 1.0f / DET;

    result[0][0] = (data[1][1] * data[2][2] - data[1][2] * data[2][1]) * INV_DET;
    result[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) * INV_DET;
    result[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * INV_DET;

    result[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) * INV_DET;
    result[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * INV_DET;
    result[1][2] = (data[0][2] * data[1][0] - data[0][0] * data[1][2]) * INV_DET;

    result[2][0] = (data[1][0] * data[2][1] - data[1][1] * data[2][0]) * INV_DET;
    result[2][1] = (data[0][1] * data[2][0] - data[0][0] * data[2][1]) * INV_DET;
    result[2][2] = (data[0][0] * data[1][1] - data[0][1] * data[1][0]) * INV_DET;

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

    const float C = std::cos(angle);
    const float S = std::sin(angle);

    result[0][0] = C;
    result[0][1] = -S;
    result[1][0] = S;
    result[1][1] = C;

    return result;
}

Matrix3 Matrix3::rotation(const Quaternion &quat)
{
    Quaternion n = quat.normalized();

    Matrix3 result(1.0f);

    const float XX = n.x * n.x;
    const float YY = n.y * n.y;
    const float ZZ = n.z * n.z;

    const float XY = n.x * n.y;
    const float XZ = n.x * n.z;
    const float YZ = n.y * n.z;

    const float WX = n.w * n.x;
    const float WY = n.w * n.y;
    const float WZ = n.w * n.z;

    result[0][0] = 1.0f - 2.0f * (YY + ZZ);
    result[0][1] = 2.0f * (XY - WZ);
    result[0][2] = 2.0f * (XZ + WY);

    result[1][0] = 2.0f * (XY + WZ);
    result[1][1] = 1.0f - 2.0f * (XX + ZZ);
    result[1][2] = 2.0f * (YZ - WX);

    result[2][0] = 2.0f * (XZ - WY);
    result[2][1] = 2.0f * (YZ + WX);
    result[2][2] = 1.0f - 2.0f * (XX + YY);

    return result;
}

Matrix3 Matrix3::scale(const Vector2D &scale)
{
    Matrix3 result = Matrix3::identity();

    result[0][0] = scale.x;
    result[1][1] = scale.y;

    return result;
}

Vector2D Matrix3::transform_point(const Vector2D &point) const
{
    return Vector2D(
        data[0][0] * point.x + data[0][1] * point.y + data[0][2],
        data[1][0] * point.x + data[1][1] * point.y + data[1][2]
    );
}

Vector2D Matrix3::transform_direction(const Vector2D &direction) const
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
            if (!Math::approximately_equal(data[row][column], other[row][column]))
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
