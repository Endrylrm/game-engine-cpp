#include "engine/core/math/Vector2D.hpp"

#include "engine/core/math/Math.hpp"
#include "engine/core/math/Vector3D.hpp"
#include "engine/core/math/Vector4D.hpp"

Vector2D::Vector2D(Vector3D vec) : Vector2D(vec.x, vec.y) {}
Vector2D::Vector2D(Vector4D vec) : Vector2D(vec.x, vec.y) {}

Vector2D Vector2D::zero()
{
    return Vector2D{0.0f, 0.0f};
}

Vector2D Vector2D::one()
{
    return Vector2D{1.0f, 1.0f};
}

Vector2D Vector2D::up()
{
    return {0.0f, -1.0f};
}

Vector2D Vector2D::down()
{
    return {0.0f, 1.0f};
}

Vector2D Vector2D::left()
{
    return {-1.0f, 0.0f};
}

Vector2D Vector2D::right()
{
    return {1.0f, 0.0f};
}

float Vector2D::length() const
{
    float vector_length = std::hypot(x, y);
    return vector_length;
}

float Vector2D::length_squared() const
{
    return x * x + y * y;
}

void Vector2D::normalize()
{
    float vector_length = length();

    if (vector_length > 0.0f)
    {
        x /= vector_length;
        y /= vector_length;
    }
}

Vector2D Vector2D::normalized() const
{
    const float VECTOR_LENGTH = length();

    if (VECTOR_LENGTH < Math::EPSILON)
        return Vector2D{0.0f, 0.0f};

    const float INV_LENGTH = 1.0f / VECTOR_LENGTH;
    return Vector2D{x * INV_LENGTH, y * INV_LENGTH};
}

float Vector2D::distance(const Vector2D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;

    return std::sqrt(dx * dx + dy * dy);
}

float Vector2D::distance_squared(const Vector2D &other) const
{
    float dx = other.x - x;
    float dy = other.y - y;

    return dx * dx + dy * dy;
}

float Vector2D::dot(const Vector2D &other) const
{
    return x * other.x + y * other.y;
}

float Vector2D::cross(const Vector2D &other) const
{
    return x * other.y - y * other.x;
}

float Vector2D::angle() const
{
    return std::atan2(y, x);
}

float Vector2D::angle_degrees() const
{
    return std::atan2(y, x) * 180.0f / Math::PI;
}

float Vector2D::angle_to(const Vector2D &other) const
{
    return std::atan2(cross(other), dot(other));
}

Vector2D Vector2D::move_towards(const Vector2D &target, float max_distance_delta) const
{
    Vector2D delta = target - *this;

    float distance = delta.length();

    if (distance <= max_distance_delta || distance == 0.0f)
        return target;

    return *this + delta / distance * max_distance_delta;
}

Vector2D Vector2D::rotate(float radians) const
{
    float c = std::cos(radians);
    float s = std::sin(radians);

    return {x * c - y * s, x * s + y * c};
}

Vector2D Vector2D::lerp(const Vector2D &target, float t) const
{
    return {x + (target.x - x) * t, y + (target.y - y) * t};
}

Vector2D Vector2D::project(const Vector2D &onto) const
{
    float length_sq = onto.length_squared();

    if (length_sq == 0.0f)
        return Vector2D(0.0f, 0.0f);

    return onto * (dot(onto) / length_sq);
}

Vector2D Vector2D::reflect(const Vector2D &normal) const
{
    return *this - normal * (2.0f * dot(normal));
}

Vector2D Vector2D::clamp_magnitude(float max_length) const
{
    float vector_length = length();

    if (vector_length <= max_length)
        return *this;

    return normalized() * max_length;
}

Vector2D Vector2D::perpendicular_left() const
{
    return {y, -x};
}

Vector2D Vector2D::perpendicular_right() const
{
    return {-y, x};
}

Vector2D Vector2D::operator+(const Vector2D &other) const
{
    return Vector2D{x + other.x, y + other.y};
}

Vector2D &Vector2D::operator+=(const Vector2D &other)
{
    *this = *this + other;
    return *this;
}

Vector2D Vector2D::operator-() const
{
    return Vector2D{-x, -y};
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
    return Vector2D{x - other.x, y - other.y};
}

Vector2D &Vector2D::operator-=(const Vector2D &other)
{
    *this = *this - other;
    return *this;
}

Vector2D Vector2D::operator*(float scalar) const
{
    return Vector2D{x * scalar, y * scalar};
}

Vector2D &Vector2D::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector2D operator*(float scalar, const Vector2D &vector)
{
    return vector * scalar;
}

Vector2D Vector2D::operator/(float scalar) const
{
    return Vector2D{x / scalar, y / scalar};
}

Vector2D &Vector2D::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

Vector2D &Vector2D::operator=(const Vector3D &other)
{
    x = other.x;
    y = other.y;

    return *this;
}

Vector2D &Vector2D::operator=(const Vector4D &other)
{
    x = other.x;
    y = other.y;

    return *this;
}

bool Vector2D::operator==(const Vector2D &other) const
{
    return Math::approximately_equal(x, other.x) && Math::approximately_equal(y, other.y);
}

bool Vector2D::operator!=(const Vector2D &other) const
{
    return !(*this == other);
}
