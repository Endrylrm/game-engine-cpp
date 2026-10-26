#include "engine/core/math/Matrix4.hpp"

#include "engine/core/math/Math.hpp"

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
    const float A = data[0][0];
    const float B = data[0][1];
    const float C = data[0][2];
    const float D = data[0][3];

    const float E = data[1][0];
    const float F = data[1][1];
    const float G = data[1][2];
    const float H = data[1][3];

    const float I = data[2][0];
    const float J = data[2][1];
    const float K = data[2][2];
    const float L = data[2][3];

    const float M = data[3][0];
    const float N = data[3][1];
    const float O = data[3][2];
    const float P = data[3][3];

    const float DET0 = F * (K * P - L * O) - G * (J * P - L * N) + H * (J * O - K * N);
    const float DET1 = E * (K * P - L * O) - G * (I * P - L * M) + H * (I * O - K * M);
    const float DET2 = E * (J * P - L * N) - F * (I * P - L * M) + H * (I * N - J * M);
    const float DET3 = E * (J * O - K * N) - F * (I * O - K * M) + G * (I * N - J * M);

    return A * DET0 - B * DET1 + C * DET2 - D * DET3;
}

Matrix4 Matrix4::inverse() const
{
    const float DET = determinant();

    if (std::abs(DET) < Math::EPSILON)
        return Matrix4::identity();

    const float INV_DET = 1.0f / DET;

    Matrix4 result;

    const float A = data[0][0];
    const float B = data[0][1];
    const float C = data[0][2];
    const float D = data[0][3];

    const float E = data[1][0];
    const float F = data[1][1];
    const float G = data[1][2];
    const float H = data[1][3];

    const float I = data[2][0];
    const float J = data[2][1];
    const float K = data[2][2];
    const float L = data[2][3];

    const float M = data[3][0];
    const float N = data[3][1];
    const float O = data[3][2];
    const float P = data[3][3];

    result[0][0] = (F * (K * P - L * O) - G * (J * P - L * N) + H * (J * O - K * N)) * INV_DET;
    result[0][1] = -(B * (K * P - L * O) - C * (J * P - L * N) + D * (J * O - K * N)) * INV_DET;
    result[0][2] = (B * (G * L - H * K) - C * (F * L - H * J) + D * (F * K - G * J)) * INV_DET;
    result[0][3] = -(B * (G * O - H * N) - C * (F * O - H * M) + D * (F * N - G * M)) * INV_DET;

    result[1][0] = -(E * (K * P - L * O) - G * (I * P - L * M) + H * (I * O - K * M)) * INV_DET;
    result[1][1] = (A * (K * P - L * O) - C * (I * P - L * M) + D * (I * O - K * M)) * INV_DET;
    result[1][2] = -(A * (G * P - H * O) - C * (E * P - H * M) + D * (E * O - G * M)) * INV_DET;
    result[1][3] = (A * (G * O - H * N) - C * (E * O - H * M) + D * (E * N - G * M)) * INV_DET;

    result[2][0] = (E * (J * P - L * N) - F * (I * P - L * M) + H * (I * N - J * M)) * INV_DET;
    result[2][1] = -(A * (J * P - L * N) - B * (I * P - L * M) + D * (I * N - J * M)) * INV_DET;
    result[2][2] = (A * (F * P - H * N) - B * (E * P - H * M) + D * (E * N - F * M)) * INV_DET;
    result[2][3] = -(A * (F * O - G * N) - B * (E * O - G * M) + C * (E * N - F * M)) * INV_DET;

    result[3][0] = -(E * (J * O - K * N) - F * (I * O - K * M) + G * (I * N - J * M)) * INV_DET;
    result[3][1] = (A * (J * O - K * N) - B * (I * O - K * M) + C * (I * N - J * M)) * INV_DET;
    result[3][2] = -(A * (F * O - G * N) - B * (E * O - G * M) + C * (E * N - F * M)) * INV_DET;
    result[3][3] = (A * (F * K - G * J) - B * (E * K - G * I) + C * (E * J - F * I)) * INV_DET;

    return result;
}

bool Matrix4::try_inverse(Matrix4 &result) const
{
    const float DET = determinant();

    if (std::abs(DET) < Math::EPSILON)
        return false;

    const float INV_DET = 1.0f / DET;

    const float A = data[0][0];
    const float B = data[0][1];
    const float C = data[0][2];
    const float D = data[0][3];

    const float E = data[1][0];
    const float F = data[1][1];
    const float G = data[1][2];
    const float H = data[1][3];

    const float I = data[2][0];
    const float J = data[2][1];
    const float K = data[2][2];
    const float L = data[2][3];

    const float M = data[3][0];
    const float N = data[3][1];
    const float O = data[3][2];
    const float P = data[3][3];

    result[0][0] = (F * (K * P - L * O) - G * (J * P - L * N) + H * (J * O - K * N)) * INV_DET;
    result[0][1] = -(B * (K * P - L * O) - C * (J * P - L * N) + D * (J * O - K * N)) * INV_DET;
    result[0][2] = (B * (G * L - H * K) - C * (F * L - H * J) + D * (F * K - G * J)) * INV_DET;
    result[0][3] = -(B * (G * O - H * N) - C * (F * O - H * M) + D * (F * N - G * M)) * INV_DET;

    result[1][0] = -(E * (K * P - L * O) - G * (I * P - L * M) + H * (I * O - K * M)) * INV_DET;
    result[1][1] = (A * (K * P - L * O) - C * (I * P - L * M) + D * (I * O - K * M)) * INV_DET;
    result[1][2] = -(A * (G * P - H * O) - C * (E * P - H * M) + D * (E * O - G * M)) * INV_DET;
    result[1][3] = (A * (G * O - H * N) - C * (E * O - H * M) + D * (E * N - G * M)) * INV_DET;

    result[2][0] = (E * (J * P - L * N) - F * (I * P - L * M) + H * (I * N - J * M)) * INV_DET;
    result[2][1] = -(A * (J * P - L * N) - B * (I * P - L * M) + D * (I * N - J * M)) * INV_DET;
    result[2][2] = (A * (F * P - H * N) - B * (E * P - H * M) + D * (E * N - F * M)) * INV_DET;
    result[2][3] = -(A * (F * O - G * N) - B * (E * O - G * M) + C * (E * N - F * M)) * INV_DET;

    result[3][0] = -(E * (J * O - K * N) - F * (I * O - K * M) + G * (I * N - J * M)) * INV_DET;
    result[3][1] = (A * (J * O - K * N) - B * (I * O - K * M) + C * (I * N - J * M)) * INV_DET;
    result[3][2] = -(A * (F * O - G * N) - B * (E * O - G * M) + C * (E * N - F * M)) * INV_DET;
    result[3][3] = (A * (F * K - G * J) - B * (E * K - G * I) + C * (E * J - F * I)) * INV_DET;

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

Matrix3 Matrix4::upper_left3x3() const
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

Matrix3 Matrix4::normal_matrix() const
{
    return upper_left3x3().inverse().transpose();
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
    const Vector3D NORMALIZED_AXIS = axis.normalized();

    const float X = NORMALIZED_AXIS.x;
    const float Y = NORMALIZED_AXIS.y;
    const float Z = NORMALIZED_AXIS.z;

    const float COSINE = std::cos(angle);
    const float SINE = std::sin(angle);
    const float ONE_MINUS_COSINE = 1.0f - COSINE;

    Matrix4 result = Matrix4::identity();

    result[0][0] = COSINE + X * X * ONE_MINUS_COSINE;
    result[0][1] = X * Y * ONE_MINUS_COSINE - Z * SINE;
    result[0][2] = X * Z * ONE_MINUS_COSINE + Y * SINE;

    result[1][0] = Y * X * ONE_MINUS_COSINE + Z * SINE;
    result[1][1] = COSINE + Y * Y * ONE_MINUS_COSINE;
    result[1][2] = Y * Z * ONE_MINUS_COSINE - X * SINE;

    result[2][0] = Z * X * ONE_MINUS_COSINE - Y * SINE;
    result[2][1] = Z * Y * ONE_MINUS_COSINE + X * SINE;
    result[2][2] = COSINE + Z * Z * ONE_MINUS_COSINE;

    return result;
}

Matrix4 Matrix4::rotation(const Quaternion &quat)
{
    Quaternion n = quat.normalized();

    Matrix4 result = Matrix4::identity();

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

Matrix4 Matrix4::rotation_x(float angle)
{
    Matrix4 result = Matrix4::identity();

    const float COSINE = std::cos(angle);
    const float SINE = std::sin(angle);

    result[1][1] = COSINE;
    result[1][2] = -SINE;

    result[2][1] = SINE;
    result[2][2] = COSINE;

    return result;
}

Matrix4 Matrix4::rotation_y(float angle)
{
    Matrix4 result = Matrix4::identity();

    const float COSINE = std::cos(angle);
    const float SINE = std::sin(angle);

    result[0][0] = COSINE;
    result[0][2] = SINE;

    result[2][0] = -SINE;
    result[2][2] = COSINE;

    return result;
}

Matrix4 Matrix4::rotation_z(float angle)
{
    Matrix4 result = Matrix4::identity();

    const float COSINE = std::cos(angle);
    const float SINE = std::sin(angle);

    result[0][0] = COSINE;
    result[0][1] = -SINE;

    result[1][0] = SINE;
    result[1][1] = COSINE;

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

Vector3D Matrix4::transform_point(const Vector3D &point) const
{
    const Vector4D RESULT = *this * Vector4D{point.x, point.y, point.z, 1.0f};

    return {RESULT.x, RESULT.y, RESULT.z};
}

Vector3D Matrix4::transform_direction(const Vector3D &direction) const
{
    const Vector4D RESULT = *this * Vector4D{direction.x, direction.y, direction.z, 0.0f};

    return {RESULT.x, RESULT.y, RESULT.z};
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

    const float TAN_HALF_FOV = std::tan(fov * 0.5f);

    result[0][0] = 1.0f / (aspect * TAN_HALF_FOV);
    result[1][1] = 1.0f / TAN_HALF_FOV;

    result[2][2] = -(far + near) / (far - near);
    result[2][3] = -(2.0f * far * near) / (far - near);

    result[3][2] = -1.0f;

    return result;
}

Matrix4 Matrix4::look_at(const Vector3D &eye, const Vector3D &target, const Vector3D &up)
{
    const Vector3D FORWARD = (target - eye).normalized();
    const Vector3D RIGHT = up.cross(FORWARD).normalized();
    const Vector3D CAMERA_UP = FORWARD.cross(RIGHT);

    Matrix4 result = Matrix4::identity();

    result[0][0] = RIGHT.x;
    result[0][1] = RIGHT.y;
    result[0][2] = RIGHT.z;
    result[0][3] = -RIGHT.dot(eye);

    result[1][0] = CAMERA_UP.x;
    result[1][1] = CAMERA_UP.y;
    result[1][2] = CAMERA_UP.z;
    result[1][3] = -CAMERA_UP.dot(eye);

    result[2][0] = -FORWARD.x;
    result[2][1] = -FORWARD.y;
    result[2][2] = -FORWARD.z;
    result[2][3] = FORWARD.dot(eye);

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
            if (!Math::approximately_equal(data[row][column], other[row][column]))
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
