#include "engine/core/math/Matrix4.hpp"

#include <engine/core/math/Math.hpp>

Matrix4::Matrix4(float diagonal) : data{}
{
    data[0][0] = diagonal;
    data[1][1] = diagonal;
    data[2][2] = diagonal;
    data[3][3] = diagonal;
}

// Matrix operations
Matrix4 Matrix4::identity()
{
    return Matrix4(1.0f);
}

float Matrix4::determinant() const
{
    const float a = data[0][0];
    const float b = data[0][1];
    const float c = data[0][2];
    const float d = data[0][3];

    const float e = data[1][0];
    const float f = data[1][1];
    const float g = data[1][2];
    const float h = data[1][3];

    const float i = data[2][0];
    const float j = data[2][1];
    const float k = data[2][2];
    const float l = data[2][3];

    const float m = data[3][0];
    const float n = data[3][1];
    const float o = data[3][2];
    const float p = data[3][3];

    const float det0 = f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n);
    const float det1 = e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m);
    const float det2 = e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m);
    const float det3 = e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m);

    return a * det0 - b * det1 + c * det2 - d * det3;
}

Matrix4 Matrix4::inverse() const
{
    const float det = determinant();

    if (std::abs(det) < Math::EPSILON)
        return Matrix4::identity();

    const float invDet = 1.0f / det;

    Matrix4 result;

    const float a = data[0][0];
    const float b = data[0][1];
    const float c = data[0][2];
    const float d = data[0][3];

    const float e = data[1][0];
    const float f = data[1][1];
    const float g = data[1][2];
    const float h = data[1][3];

    const float i = data[2][0];
    const float j = data[2][1];
    const float k = data[2][2];
    const float l = data[2][3];

    const float m = data[3][0];
    const float n = data[3][1];
    const float o = data[3][2];
    const float p = data[3][3];

    result[0][0] = (f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n)) * invDet;
    result[0][1] = -(b * (k * p - l * o) - c * (j * p - l * n) + d * (j * o - k * n)) * invDet;
    result[0][2] = (b * (g * l - h * k) - c * (f * l - h * j) + d * (f * k - g * j)) * invDet;
    result[0][3] = -(b * (g * o - h * n) - c * (f * o - h * m) + d * (f * n - g * m)) * invDet;

    result[1][0] = -(e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m)) * invDet;
    result[1][1] = (a * (k * p - l * o) - c * (i * p - l * m) + d * (i * o - k * m)) * invDet;
    result[1][2] = -(a * (g * p - h * o) - c * (e * p - h * m) + d * (e * o - g * m)) * invDet;
    result[1][3] = (a * (g * o - h * n) - c * (e * o - h * m) + d * (e * n - g * m)) * invDet;

    result[2][0] = (e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m)) * invDet;
    result[2][1] = -(a * (j * p - l * n) - b * (i * p - l * m) + d * (i * n - j * m)) * invDet;
    result[2][2] = (a * (f * p - h * n) - b * (e * p - h * m) + d * (e * n - f * m)) * invDet;
    result[2][3] = -(a * (f * o - g * n) - b * (e * o - g * m) + c * (e * n - f * m)) * invDet;

    result[3][0] = -(e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m)) * invDet;
    result[3][1] = (a * (j * o - k * n) - b * (i * o - k * m) + c * (i * n - j * m)) * invDet;
    result[3][2] = -(a * (f * o - g * n) - b * (e * o - g * m) + c * (e * n - f * m)) * invDet;
    result[3][3] = (a * (f * k - g * j) - b * (e * k - g * i) + c * (e * j - f * i)) * invDet;

    return result;
}

bool Matrix4::tryInverse(Matrix4 &result) const
{
    const float det = determinant();

    if (std::abs(det) < Math::EPSILON)
        return false;

    const float invDet = 1.0f / det;

    const float a = data[0][0];
    const float b = data[0][1];
    const float c = data[0][2];
    const float d = data[0][3];

    const float e = data[1][0];
    const float f = data[1][1];
    const float g = data[1][2];
    const float h = data[1][3];

    const float i = data[2][0];
    const float j = data[2][1];
    const float k = data[2][2];
    const float l = data[2][3];

    const float m = data[3][0];
    const float n = data[3][1];
    const float o = data[3][2];
    const float p = data[3][3];

    result[0][0] = (f * (k * p - l * o) - g * (j * p - l * n) + h * (j * o - k * n)) * invDet;
    result[0][1] = -(b * (k * p - l * o) - c * (j * p - l * n) + d * (j * o - k * n)) * invDet;
    result[0][2] = (b * (g * l - h * k) - c * (f * l - h * j) + d * (f * k - g * j)) * invDet;
    result[0][3] = -(b * (g * o - h * n) - c * (f * o - h * m) + d * (f * n - g * m)) * invDet;

    result[1][0] = -(e * (k * p - l * o) - g * (i * p - l * m) + h * (i * o - k * m)) * invDet;
    result[1][1] = (a * (k * p - l * o) - c * (i * p - l * m) + d * (i * o - k * m)) * invDet;
    result[1][2] = -(a * (g * p - h * o) - c * (e * p - h * m) + d * (e * o - g * m)) * invDet;
    result[1][3] = (a * (g * o - h * n) - c * (e * o - h * m) + d * (e * n - g * m)) * invDet;

    result[2][0] = (e * (j * p - l * n) - f * (i * p - l * m) + h * (i * n - j * m)) * invDet;
    result[2][1] = -(a * (j * p - l * n) - b * (i * p - l * m) + d * (i * n - j * m)) * invDet;
    result[2][2] = (a * (f * p - h * n) - b * (e * p - h * m) + d * (e * n - f * m)) * invDet;
    result[2][3] = -(a * (f * o - g * n) - b * (e * o - g * m) + c * (e * n - f * m)) * invDet;

    result[3][0] = -(e * (j * o - k * n) - f * (i * o - k * m) + g * (i * n - j * m)) * invDet;
    result[3][1] = (a * (j * o - k * n) - b * (i * o - k * m) + c * (i * n - j * m)) * invDet;
    result[3][2] = -(a * (f * o - g * n) - b * (e * o - g * m) + c * (e * n - f * m)) * invDet;
    result[3][3] = (a * (f * k - g * j) - b * (e * k - g * i) + c * (e * j - f * i)) * invDet;

    return true;
}

Matrix4 Matrix4::transpose() const
{
    Matrix4 result;

    for (size_t row = 0; row < 4; ++row)
    {
        for (size_t column = 0; column < 4; ++column)
        {
            result[row][column] = data[column][row];
        }
    }

    return result;
}

Matrix3 Matrix4::upperLeft3x3() const
{
    Matrix3 result;

    for (size_t row = 0; row < 3; ++row)
    {
        for (size_t column = 0; column < 3; ++column)
        {
            result[row][column] = data[row][column];
        }
    }

    return result;
}

Matrix3 Matrix4::normalMatrix() const
{
    return upperLeft3x3().inverse().transpose();
}

// Transformations
Matrix4 Matrix4::translation(const Vector3D &translation)
{
    Matrix4 result = Matrix4::identity();

    result[0][3] = translation.x;
    result[1][3] = translation.y;
    result[2][3] = translation.z;

    return result;
}

Matrix4 Matrix4::rotation(float angle, const Vector3D &axis)
{
    const Vector3D normalizedAxis = axis.normalized();

    const float x = normalizedAxis.x;
    const float y = normalizedAxis.y;
    const float z = normalizedAxis.z;

    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);
    const float oneMinusCosine = 1.0f - cosine;

    Matrix4 result = Matrix4::identity();

    result[0][0] = cosine + x * x * oneMinusCosine;
    result[0][1] = x * y * oneMinusCosine - z * sine;
    result[0][2] = x * z * oneMinusCosine + y * sine;

    result[1][0] = y * x * oneMinusCosine + z * sine;
    result[1][1] = cosine + y * y * oneMinusCosine;
    result[1][2] = y * z * oneMinusCosine - x * sine;

    result[2][0] = z * x * oneMinusCosine - y * sine;
    result[2][1] = z * y * oneMinusCosine + x * sine;
    result[2][2] = cosine + z * z * oneMinusCosine;

    return result;
}

Matrix4 Matrix4::rotation(const Quaternion &quat)
{
    Quaternion n = quat.normalized();
    Matrix4 result(1.0f);

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

Matrix4 Matrix4::rotationX(float angle)
{
    Matrix4 result = Matrix4::identity();

    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);

    result[1][1] = cosine;
    result[1][2] = -sine;

    result[2][1] = sine;
    result[2][2] = cosine;

    return result;
}

Matrix4 Matrix4::rotationY(float angle)
{
    Matrix4 result = Matrix4::identity();

    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);

    result[0][0] = cosine;
    result[0][2] = sine;

    result[2][0] = -sine;
    result[2][2] = cosine;

    return result;
}

Matrix4 Matrix4::rotationZ(float angle)
{
    Matrix4 result = Matrix4::identity();

    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);

    result[0][0] = cosine;
    result[0][1] = -sine;

    result[1][0] = sine;
    result[1][1] = cosine;

    return result;
}

Matrix4 Matrix4::scale(const Vector3D &scale)
{
    Matrix4 result = Matrix4::identity();

    result[0][0] = scale.x;
    result[1][1] = scale.y;
    result[2][2] = scale.z;

    return result;
}

Vector3D Matrix4::transformPoint(const Vector3D &point) const
{
    const Vector4D result = *this * Vector4D{point.x, point.y, point.z, 1.0f};

    return {result.x, result.y, result.z};
}

Vector3D Matrix4::transformDirection(const Vector3D &direction) const
{
    const Vector4D result = *this * Vector4D{direction.x, direction.y, direction.z, 0.0f};

    return {result.x, result.y, result.z};
}

// Projection
Matrix4
Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
    Matrix4 result{};

    result[0][0] = 2.0f / (right - left);
    result[1][1] = 2.0f / (top - bottom);
    result[2][2] = -2.0f / (far - near);

    result[0][3] = -(right + left) / (right - left);
    result[1][3] = -(top + bottom) / (top - bottom);
    result[2][3] = -(far + near) / (far - near);

    result[3][3] = 1.0f;

    return result;
}

Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far)
{
    Matrix4 result{};

    const float tanHalfFov = std::tan(fov * 0.5f);

    result[0][0] = 1.0f / (aspect * tanHalfFov);
    result[1][1] = 1.0f / tanHalfFov;

    result[2][2] = -(far + near) / (far - near);
    result[2][3] = -(2.0f * far * near) / (far - near);

    result[3][2] = -1.0f;

    return result;
}

Matrix4 Matrix4::lookAt(const Vector3D &eye, const Vector3D &target, const Vector3D &up)
{
    const Vector3D forward = (target - eye).normalized();
    const Vector3D right = forward.cross(up).normalized();
    const Vector3D cameraUp = right.cross(forward);

    Matrix4 result = Matrix4::identity();

    result[0][0] = right.x;
    result[0][1] = right.y;
    result[0][2] = right.z;
    result[0][3] = -right.dot(eye);

    result[1][0] = cameraUp.x;
    result[1][1] = cameraUp.y;
    result[1][2] = cameraUp.z;
    result[1][3] = -cameraUp.dot(eye);

    result[2][0] = -forward.x;
    result[2][1] = -forward.y;
    result[2][2] = -forward.z;
    result[2][3] = forward.dot(eye);

    return result;
}

// Operators
Matrix4 Matrix4::operator+(const Matrix4 &other) const
{
    Matrix4 result;

    for (size_t row = 0; row < 4; ++row)
    {
        for (size_t column = 0; column < 4; ++column)
        {
            result[row][column] = data[row][column] + other[row][column];
        }
    }

    return result;
}

Matrix4 &Matrix4::operator+=(const Matrix4 &other)
{
    *this = *this + other;
    return *this;
}

Matrix4 Matrix4::operator-(const Matrix4 &other) const
{
    Matrix4 result;

    for (size_t row = 0; row < 4; ++row)
    {
        for (size_t column = 0; column < 4; ++column)
        {
            result[row][column] = data[row][column] - other[row][column];
        }
    }

    return result;
}

Matrix4 &Matrix4::operator-=(const Matrix4 &other)
{
    *this = *this - other;
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 &other) const
{
    Matrix4 result;

    for (size_t row = 0; row < 4; ++row)
    {
        for (size_t column = 0; column < 4; ++column)
        {
            result[row][column] = 0.0f;

            for (size_t k = 0; k < 4; ++k)
            {
                result[row][column] += data[row][k] * other[k][column];
            }
        }
    }

    return result;
}

Matrix4 &Matrix4::operator*=(const Matrix4 &other)
{
    *this = *this * other;
    return *this;
}

Matrix4 Matrix4::operator*(float scalar) const
{
    Matrix4 result;

    for (size_t row = 0; row < 4; ++row)
    {
        for (size_t column = 0; column < 4; ++column)
        {
            result[row][column] = data[row][column] * scalar;
        }
    }

    return result;
}

Matrix4 &Matrix4::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector4D Matrix4::operator*(const Vector4D &vector) const
{
    return Vector4D{
        data[0][0] * vector.x + data[0][1] * vector.y + data[0][2] * vector.z +
            data[0][3] * vector.w,
        data[1][0] * vector.x + data[1][1] * vector.y + data[1][2] * vector.z +
            data[1][3] * vector.w,
        data[2][0] * vector.x + data[2][1] * vector.y + data[2][2] * vector.z +
            data[2][3] * vector.w,
        data[3][0] * vector.x + data[3][1] * vector.y + data[3][2] * vector.z +
            data[3][3] * vector.w
    };
}

bool Matrix4::operator==(const Matrix4 &other) const
{
    for (size_t row = 0; row < 4; ++row)
    {
        for (size_t column = 0; column < 4; ++column)
        {
            if (!Math::approximatelyEqual(data[row][column], other[row][column]))
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix4::operator!=(const Matrix4 &other) const
{
    return !(*this == other);
}

float *Matrix4::operator[](size_t row)
{
    return data[row];
}

const float *Matrix4::operator[](size_t row) const
{
    return data[row];
}
