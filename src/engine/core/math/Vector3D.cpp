#include "engine/core/math/Vector3D.hpp"

#include "engine/core/math/Math.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/core/math/Vector4D.hpp"

Vector3D::Vector3D(Vector2D vec) : Vector3D(vec.x, vec.y, 0.0f) {}
Vector3D::Vector3D(Vector2D vec, float z) : Vector3D(vec.x, vec.y, z) {}
Vector3D::Vector3D(Vector4D vec) : Vector3D(vec.x, vec.y, vec.z) {}

Vector3D Vector3D::zero()
{
    return Vector3D{0.0f, 0.0f, 0.0f};
}

Vector3D Vector3D::one()
{
    return Vector3D{1.0f, 1.0f, 1.0f};
}

Vector3D Vector3D::up()
{
    return {0.0f, -1.0f, 0.0f};
}

Vector3D Vector3D::down()
{
    return {0.0f, 1.0f, 0.0f};
}

Vector3D Vector3D::left()
{
    return {-1.0f, 0.0f, 0.0f};
}

Vector3D Vector3D::right()
{
    return {1.0f, 0.0f, 0.0f};
}

Vector3D Vector3D::forward()
{
    return {0.0f, 0.0f, 1.0f};
}

Vector3D Vector3D::back()
{
    return {0.0f, 0.0f, -1.0f};
}

bool Vector3D::is_zero() const
{
    return length_squared() < Math::EPSILON;
}

float Vector3D::length() const
{
    float vector_length = std::hypot(std::hypot(x, y), z);
    return vector_length;
}

float Vector3D::length_squared() const
{
    return x * x + y * y + z * z;
}

void Vector3D::normalize()
{
    float vector_length = length();

    if (vector_length > 0.0f)
    {
        x /= vector_length;
        y /= vector_length;
        z /= vector_length;
    }
}

Vector3D Vector3D::normalized() const
{
    float vector_length = length();

    if (vector_length < Math::EPSILON)
        return {0.0f, 0.0f, 0.0f};

    return {x / vector_length, y / vector_length, z / vector_length};
}

float Vector3D::distance(const Vector3D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;
    float dz = other.z - z;

    return std::hypot(std::hypot(dx, dy), dz);
}

float Vector3D::distance_squared(const Vector3D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;
    float dz = other.z - z;

    return dx * dx + dy * dy + dz * dz;
}

float Vector3D::dot(const Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return Vector3D(
        y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x
    );
}

float Vector3D::angle(const Vector3D &other) const
{
    float lengths = length() * other.length();

    if (lengths <= Math::EPSILON)
        return 0.0f;

    float cosine = dot(other) / lengths;
    cosine = std::clamp(cosine, -1.0f, 1.0f);
    return std::acos(cosine);
}

float Vector3D::angle_degrees(const Vector3D &other) const
{
    return angle(other) * 180.0f / Math::PI;
}

float Vector3D::pitch() const
{
    return std::atan2(y, std::hypot(x * x, z * z));
}

float Vector3D::pitch_degrees() const
{
    return std::atan2(z, std::hypot(x * x, y * y)) * 180.0f / Math::PI;
}

float Vector3D::yaw() const
{
    return std::atan2(x, z);
}

float Vector3D::yaw_degrees() const
{
    return std::atan2(y, x) * 180.0f / Math::PI;
}

Vector3D Vector3D::move_towards(const Vector3D &target, float max_distance_delta) const
{
    Vector3D delta = target - *this;

    float distance = delta.length();

    if (distance <= max_distance_delta || distance < Math::EPSILON)
        return target;

    return *this + delta / distance * max_distance_delta;
}

Vector3D Vector3D::rotate_towards(const Vector3D &target, float max_radians_delta) const
{
    Vector3D from = normalized();
    Vector3D to = target.normalized();

    float dot_product = from.dot(to);

    dot_product = std::clamp(dot_product, -1.0f, 1.0f);

    float angle = std::acos(dot_product);

    if (angle < Math::EPSILON)
        return target;

    float t = std::min(1.0f, max_radians_delta / angle);

    float sin_angle = std::sin(angle);

    float a = std::sin((1.0f - t) * angle) / sin_angle;
    float b = std::sin(t * angle) / sin_angle;

    return (from * a + to * b);
}

Vector3D Vector3D::lerp(const Vector3D &target, float t) const
{
    return {x + (target.x - x) * t, y + (target.y - y) * t, z + (target.z - z) * t};
}

Vector3D Vector3D::project(const Vector3D &onto) const
{
    float length_sq = onto.length_squared();

    if (length_sq == 0.0f)
        return Vector3D(0.0f);

    return onto * (dot(onto) / length_sq);
}

Vector3D Vector3D::reflect(const Vector3D &normal) const
{
    return *this - normal * (2.0f * dot(normal));
}

Vector3D Vector3D::clamp_magnitude(float max_length) const
{
    float vector_length = length();

    if (vector_length <= max_length)
        return *this;

    return normalized() * max_length;
}

Vector3D Vector3D::perpendicular() const
{
    const float ABS_X = std::abs(x);
    const float ABS_Y = std::abs(y);
    const float ABS_Z = std::abs(z);

    if (ABS_X <= ABS_Y && ABS_X <= ABS_Z)
        return cross(Vector3D::right()).normalized();

    if (ABS_Y <= ABS_Z)
        return cross(Vector3D::down()).normalized();

    return cross(Vector3D::forward()).normalized();
}

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D{x + other.x, y + other.y, z + other.z};
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    *this = *this + other;
    return *this;
}

Vector3D Vector3D::operator-() const
{
    return Vector3D{-x, -y, -z};
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D{x - other.x, y - other.y, z - other.z};
}

Vector3D &Vector3D::operator-=(const Vector3D &other)
{
    *this = *this - other;
    return *this;
}

Vector3D Vector3D::operator*(float scalar) const
{
    return Vector3D{x * scalar, y * scalar, z * scalar};
}

Vector3D &Vector3D::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector3D operator*(float scalar, const Vector3D &vector)
{
    return vector * scalar;
}

Vector3D Vector3D::operator*(const Vector3D &other) const
{
    return Vector3D{x * other.x, y * other.y, z * other.z};
}

Vector3D &Vector3D::operator*=(const Vector3D &other)
{
    *this = *this * other;
    return *this;
}

Vector3D Vector3D::operator/(float scalar) const
{
    return Vector3D{x / scalar, y / scalar, z / scalar};
}

Vector3D &Vector3D::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

Vector3D &Vector3D::operator=(const Vector2D &other)
{
    x = other.x;
    y = other.y;
    z = 0.0f;

    return *this;
}

Vector3D &Vector3D::operator=(const Vector4D &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

bool Vector3D::operator==(const Vector3D &other) const
{
    return Math::approximately_equal(x, other.x) && Math::approximately_equal(y, other.y) &&
           Math::approximately_equal(z, other.z);
}

bool Vector3D::operator!=(const Vector3D &other) const
{
    return !(*this == other);
}
