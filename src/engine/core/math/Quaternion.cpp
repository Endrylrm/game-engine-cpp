#include "engine/core/math/Quaternion.hpp"

#include <engine/core/math/Math.hpp>
#include <engine/core/math/Vector3D.hpp>

constexpr Quaternion Quaternion::identity()
{
    return Quaternion{0.0f, 0.0f, 0.0f, 1.0f};
}

Quaternion Quaternion::fromAxisAngle(const Vector3D &axis, float radians)
{
    const Vector3D normalizedAxis = axis.normalized();

    const float halfAngle = radians * 0.5f;
    const float sinHalf = std::sin(halfAngle);
    const float cosHalf = std::cos(halfAngle);

    return Quaternion{
        normalizedAxis.x * sinHalf, normalizedAxis.y * sinHalf, normalizedAxis.z * sinHalf, cosHalf
    };
}

Quaternion Quaternion::fromEuler(float pitchX, float yawY, float rollZ)
{
    const float halfPitch = pitchX * 0.5f;
    const float halfYaw = yawY * 0.5f;
    const float halfRoll = rollZ * 0.5f;

    const float cp = std::cos(halfPitch);
    const float sp = std::sin(halfPitch);

    const float cy = std::cos(halfYaw);
    const float sy = std::sin(halfYaw);

    const float cr = std::cos(halfRoll);
    const float sr = std::sin(halfRoll);

    return Quaternion{
        sp * cy * cr - cp * sy * sr,
        cp * sy * cr + sp * cy * sr,
        cp * cy * sr - sp * sy * cr,
        cp * cy * cr + sp * sy * sr
    };
}

Quaternion Quaternion::fromToRotation(const Vector3D &from, const Vector3D &to)
{
    if (from.lengthSquared() < Math::EPSILON_SQUARED || to.lengthSquared() < Math::EPSILON_SQUARED)
    {
        return identity();
    }

    const Vector3D f = from.normalized();
    const Vector3D t = to.normalized();

    const float dot = f.dot(t);

    // Same direction.
    if (dot > 1.0f - Math::EPSILON)
        return identity();

    // Opposite direction.
    if (dot < -1.0f + Math::EPSILON)
    {
        Vector3D axis;

        // Pick an axis perpendicular to 'f'.
        if (std::abs(f.x) < std::abs(f.y) && std::abs(f.x) < std::abs(f.z))
        {
            axis = f.cross(Vector3D{1.0f, 0.0f, 0.0f});
        }
        else if (std::abs(f.y) < std::abs(f.z))
        {
            axis = f.cross(Vector3D{0.0f, 1.0f, 0.0f});
        }
        else
        {
            axis = f.cross(Vector3D{0.0f, 0.0f, 1.0f});
        }

        return fromAxisAngle(axis.normalized(), Math::PI);
    }

    const Vector3D cross = f.cross(t);
    Quaternion result{cross.x, cross.y, cross.z, 1.0f + dot};
    return result.normalized();
}

Vector3D Quaternion::rotate(const Vector3D &vector) const
{
    const Quaternion vectorQuaternion{vector.x, vector.y, vector.z, 0.0f};
    const Quaternion result = *this * vectorQuaternion * conjugate();
    return Vector3D{result.x, result.y, result.z};
}

float Quaternion::lengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}

float Quaternion::length() const
{
    return std::sqrt(lengthSquared());
}

Quaternion Quaternion::normalized() const
{
    const float lengthSq = lengthSquared();

    if (lengthSq < Math::EPSILON_SQUARED)
        return identity();

    const float invLength = 1.0f / std::sqrt(lengthSq);

    return Quaternion{x * invLength, y * invLength, z * invLength, w * invLength};
}

void Quaternion::normalize()
{
    const float lengthSq = lengthSquared();

    if (lengthSq < Math::EPSILON_SQUARED)
    {
        *this = identity();
        return;
    }

    const float invLength = 1.0f / std::sqrt(lengthSq);

    x *= invLength;
    y *= invLength;
    z *= invLength;
    w *= invLength;
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion{-x, -y, -z, w};
}

Quaternion Quaternion::inverse() const
{
    const float lengthSq = lengthSquared();

    if (lengthSq < Math::EPSILON_SQUARED)
        return identity();

    return conjugate() * (1.0f / lengthSq);
}

float Quaternion::dot(const Quaternion &a, const Quaternion &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

void Quaternion::toAxisAngle(Vector3D &outAxis, float &outAngle) const
{
    const Quaternion q = normalized();
    const float clampedW = Math::clamp(q.w, -1.0f, 1.0f);
    outAngle = 2.0f * std::acos(clampedW);

    const float sinHalfAngle = std::sqrt(1.0f - clampedW * clampedW);

    if (sinHalfAngle < Math::EPSILON)
    {
        // Axis is undefined for zero rotation.
        outAxis = Vector3D{1.0f, 0.0f, 0.0f};
        return;
    }

    const float invSinHalfAngle = 1.0f / sinHalfAngle;
    outAxis = Vector3D{q.x * invSinHalfAngle, q.y * invSinHalfAngle, q.z * invSinHalfAngle};
}

Vector3D Quaternion::toEuler() const
{
    const Quaternion q = normalized();

    const float sinPitch = 2.0f * (q.w * q.x + q.y * q.z);
    const float cosPitch = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    const float pitch = std::atan2(sinPitch, cosPitch);
    const float sinYaw = 2.0f * (q.w * q.y - q.z * q.x);

    float yaw;

    if (std::abs(sinYaw) >= 1.0f)
    {
        yaw = std::copysign(Math::PI * 0.5f, sinYaw);
    }
    else
    {
        yaw = std::asin(sinYaw);
    }

    const float sinRoll = 2.0f * (q.w * q.z + q.x * q.y);
    const float cosRoll = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    const float roll = std::atan2(sinRoll, cosRoll);

    return Vector3D{pitch, yaw, roll};
}

Quaternion Quaternion::nlerp(const Quaternion &a, const Quaternion &b, float t)
{
    const float qDot = dot(a, b);
    Quaternion bAdj = (qDot < 0.0f) ? -b : b;
    return (a * (1.0f - t) + bAdj * t).normalized();
}

Quaternion Quaternion::slerp(const Quaternion &a, const Quaternion &b, float t)
{
    Quaternion q1 = a.normalized();
    Quaternion q2 = b.normalized();

    float qDot = dot(q1, q2);

    // Take the shortest path.
    if (qDot < 0.0f)
    {
        q2 = -q2;
        qDot = -qDot;
    }

    qDot = Math::clamp(qDot, -1.0f, 1.0f);

    // If the quaternions are very close,
    // use linear interpolation to avoid numerical instability.
    if (qDot > 1.0f - Math::EPSILON)
    {
        Quaternion result{
            q1.x + t * (q2.x - q1.x),
            q1.y + t * (q2.y - q1.y),
            q1.z + t * (q2.z - q1.z),
            q1.w + t * (q2.w - q1.w)
        };

        return result.normalized();
    }

    const float angle = std::acos(qDot);
    const float sinAngle = std::sin(angle);

    const float factorA = std::sin((1.0f - t) * angle) / sinAngle;

    const float factorB = std::sin(t * angle) / sinAngle;

    return Quaternion{
        q1.x * factorA + q2.x * factorB,
        q1.y * factorA + q2.y * factorB,
        q1.z * factorA + q2.z * factorB,
        q1.w * factorA + q2.w * factorB
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

Quaternion Quaternion::operator-(const Quaternion &other) const
{
    return {x - other.x, y - other.y, z - other.z, w - other.w};
}

Quaternion &Quaternion::operator-=(const Quaternion &other)
{
    *this = *this - other;
    return *this;
}

Quaternion Quaternion::operator-() const
{
    return {-x, -y, -z, -w};
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
    return Math::approximatelyEqual(x, other.x) && Math::approximatelyEqual(y, other.y) &&
           Math::approximatelyEqual(z, other.z) && Math::approximatelyEqual(w, other.w);
}

bool Quaternion::operator!=(const Quaternion &other) const
{
    return !(*this == other);
}
