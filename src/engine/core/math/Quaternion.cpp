#include "engine/core/math/Quaternion.hpp"

#include "engine/core/math/Math.hpp"
#include "engine/core/math/Vector3D.hpp"

Quaternion Quaternion::from_axis_angle(const Vector3D &axis, float radians)
{
    const Vector3D NORMALIZED_AXIS = axis.normalized();

    const float HALF_ANGLE = radians * 0.5f;
    const float SIN_HALF = std::sin(HALF_ANGLE);
    const float COS_HALF = std::cos(HALF_ANGLE);

    return Quaternion{
        NORMALIZED_AXIS.x * SIN_HALF,
        NORMALIZED_AXIS.y * SIN_HALF,
        NORMALIZED_AXIS.z * SIN_HALF,
        COS_HALF
    };
}

Quaternion Quaternion::from_euler(float pitch_x, float yaw_y, float roll_z)
{
    const float HALF_PITCH = pitch_x * 0.5f;
    const float HALF_YAW = yaw_y * 0.5f;
    const float HALF_ROLL = roll_z * 0.5f;

    const float CP = std::cos(HALF_PITCH);
    const float SP = std::sin(HALF_PITCH);

    const float CY = std::cos(HALF_YAW);
    const float SY = std::sin(HALF_YAW);

    const float CR = std::cos(HALF_ROLL);
    const float SR = std::sin(HALF_ROLL);

    return Quaternion{
        SP * CY * CR - CP * SY * SR,
        CP * SY * CR + SP * CY * SR,
        CP * CY * SR - SP * SY * CR,
        CP * CY * CR + SP * SY * SR
    };
}

Quaternion Quaternion::from_to_rotation(const Vector3D &from, const Vector3D &to)
{
    if (from.length_squared() < Math::EPSILON_SQUARED ||
        to.length_squared() < Math::EPSILON_SQUARED)
    {
        return identity();
    }

    const Vector3D F = from.normalized();
    const Vector3D T = to.normalized();

    const float DOT_PRODUCT = F.dot(T);

    // Same direction.
    if (DOT_PRODUCT > 1.0f - Math::EPSILON)
        return identity();

    // Opposite direction.
    if (DOT_PRODUCT < -1.0f + Math::EPSILON)
    {
        // Pick an axis perpendicular to 'f'.
        Vector3D axis = F.perpendicular();
        return from_axis_angle(axis.normalized(), Math::PI);
    }

    const Vector3D CROSS_PRODUCT = F.cross(T);
    Quaternion result{CROSS_PRODUCT.x, CROSS_PRODUCT.y, CROSS_PRODUCT.z, 1.0f + DOT_PRODUCT};
    return result.normalized();
}

Vector3D Quaternion::rotate(const Vector3D &vector) const
{
    const Quaternion VECTOR_QUATERNION{vector.x, vector.y, vector.z, 0.0f};
    const Quaternion RESULT = *this * VECTOR_QUATERNION * conjugate();
    return Vector3D{RESULT.x, RESULT.y, RESULT.z};
}

float Quaternion::length_squared() const
{
    return x * x + y * y + z * z + w * w;
}

float Quaternion::length() const
{
    return std::sqrt(length_squared());
}

Quaternion Quaternion::normalized() const
{
    const float LENGTH_SQ = length_squared();

    if (LENGTH_SQ < Math::EPSILON_SQUARED)
        return identity();

    const float INV_LENGTH = 1.0f / std::sqrt(LENGTH_SQ);

    return Quaternion{x * INV_LENGTH, y * INV_LENGTH, z * INV_LENGTH, w * INV_LENGTH};
}

void Quaternion::normalize()
{
    const float LENGTH_SQ = length_squared();

    if (LENGTH_SQ < Math::EPSILON_SQUARED)
    {
        *this = identity();
        return;
    }

    const float INV_LENGTH = 1.0f / std::sqrt(LENGTH_SQ);

    x *= INV_LENGTH;
    y *= INV_LENGTH;
    z *= INV_LENGTH;
    w *= INV_LENGTH;
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion{-x, -y, -z, w};
}

Quaternion Quaternion::inverse() const
{
    const float LENGTH_SQ = length_squared();

    if (LENGTH_SQ < Math::EPSILON_SQUARED)
        return identity();

    return conjugate() * (1.0f / LENGTH_SQ);
}

float Quaternion::dot(const Quaternion &a, const Quaternion &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

void Quaternion::to_axis_angle(Vector3D &out_axis, float &out_angle) const
{
    const Quaternion Q = normalized();
    const float CLAMPED_W = Math::clamp(Q.w, -1.0f, 1.0f);
    out_angle = 2.0f * std::acos(CLAMPED_W);

    const float SIN_HALF_ANGLE = std::sqrt(1.0f - CLAMPED_W * CLAMPED_W);

    if (SIN_HALF_ANGLE < Math::EPSILON)
    {
        // Axis is undefined for zero rotation.
        out_axis = Vector3D{1.0f, 0.0f, 0.0f};
        return;
    }

    const float INV_SIN_HALF_ANGLE = 1.0f / SIN_HALF_ANGLE;
    out_axis =
        Vector3D{Q.x * INV_SIN_HALF_ANGLE, Q.y * INV_SIN_HALF_ANGLE, Q.z * INV_SIN_HALF_ANGLE};
}

Vector3D Quaternion::to_euler() const
{
    const Quaternion Q = normalized();

    const float SIN_PITCH = 2.0f * (Q.w * Q.x + Q.y * Q.z);
    const float COS_PITCH = 1.0f - 2.0f * (Q.x * Q.x + Q.y * Q.y);
    const float PITCH = std::atan2(SIN_PITCH, COS_PITCH);
    const float SIN_YAW = 2.0f * (Q.w * Q.y - Q.z * Q.x);

    float yaw;

    if (std::abs(SIN_YAW) >= 1.0f)
    {
        yaw = std::copysign(Math::PI * 0.5f, SIN_YAW);
    }
    else
    {
        yaw = std::asin(SIN_YAW);
    }

    const float SIN_ROLL = 2.0f * (Q.w * Q.z + Q.x * Q.y);
    const float COS_ROLL = 1.0f - 2.0f * (Q.y * Q.y + Q.z * Q.z);
    const float ROLL = std::atan2(SIN_ROLL, COS_ROLL);

    return Vector3D{PITCH, yaw, ROLL};
}

Quaternion Quaternion::nlerp(const Quaternion &a, const Quaternion &b, float t)
{
    const float DOT_PRODUCT = dot(a, b);
    const Quaternion TARGET = (DOT_PRODUCT < 0.0f) ? -b : b;
    return (a * (1.0f - t) + TARGET * t).normalized();
}

Quaternion Quaternion::slerp(const Quaternion &a, const Quaternion &b, float t)
{
    Quaternion q1 = a.normalized();
    Quaternion q2 = b.normalized();

    float dot_product = dot(q1, q2);

    // Take the shortest path.
    if (dot_product < 0.0f)
    {
        q2 = -q2;
        dot_product = -dot_product;
    }

    dot_product = Math::clamp(dot_product, -1.0f, 1.0f);

    // If the quaternions are very close,
    // use linear interpolation to avoid numerical instability.
    if (dot_product > 1.0f - Math::EPSILON)
    {
        Quaternion result{
            q1.x + t * (q2.x - q1.x),
            q1.y + t * (q2.y - q1.y),
            q1.z + t * (q2.z - q1.z),
            q1.w + t * (q2.w - q1.w)
        };

        return result.normalized();
    }

    const float ANGLE = std::acos(dot_product);
    const float SIN_ANGLE = std::sin(ANGLE);

    const float FACTOR_A = std::sin((1.0f - t) * ANGLE) / SIN_ANGLE;

    const float FACTOR_B = std::sin(t * ANGLE) / SIN_ANGLE;

    return Quaternion{
        q1.x * FACTOR_A + q2.x * FACTOR_B,
        q1.y * FACTOR_A + q2.y * FACTOR_B,
        q1.z * FACTOR_A + q2.z * FACTOR_B,
        q1.w * FACTOR_A + q2.w * FACTOR_B
    };
}

Quaternion Quaternion::operator+(const Quaternion &other) const
{
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Quaternion &Quaternion::operator+=(const Quaternion &other)
{
    *this = *this + other;
    return *this;
}

Quaternion Quaternion::operator-() const
{
    return {-x, -y, -z, -w};
}

Quaternion Quaternion::operator-(const Quaternion &other) const
{
    return {x - other.x, y - other.y, z - other.z, w - other.w};
}

Quaternion &Quaternion::operator-=(const Quaternion &other)
{
    *this = *this - other;
    return *this;
}

Quaternion Quaternion::operator*(const Quaternion &other) const
{
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Quaternion &Quaternion::operator*=(const Quaternion &other)
{
    *this = *this * other;
    return *this;
}

Quaternion Quaternion::operator*(float scalar) const
{
    return {x * scalar, y * scalar, z * scalar, w * scalar};
}

Quaternion &Quaternion::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

bool Quaternion::operator==(const Quaternion &other) const
{
    return Math::approximately_equal(x, other.x) && Math::approximately_equal(y, other.y) &&
           Math::approximately_equal(z, other.z) && Math::approximately_equal(w, other.w);
}

bool Quaternion::operator!=(const Quaternion &other) const
{
    return !(*this == other);
}
