#pragma once
class Vector3D;
class Vector4D;

class Vector2D
{
public:
    Vector2D() : Vector2D(0.0f) {}
    Vector2D(float all) : Vector2D(all, all) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    Vector2D(const Vector2D &other) : Vector2D(other.x, other.y) {}
    Vector2D(Vector3D vec);
    Vector2D(Vector4D vec);

    static Vector2D zero();
    static Vector2D one();
    static Vector2D up();
    static Vector2D down();
    static Vector2D left();
    static Vector2D right();

    float length() const;
    float length_squared() const;

    void normalize();
    Vector2D normalized() const;

    float distance(const Vector2D &other) const;
    float distance_squared(const Vector2D &other) const;

    float dot(const Vector2D &other) const;
    float cross(const Vector2D &other) const;

    float angle() const;
    float angle_degrees() const;
    float angle_to(const Vector2D &other) const;

    Vector2D move_towards(const Vector2D &target, float max_distance_delta) const;
    Vector2D rotate(float radians) const;
    Vector2D lerp(const Vector2D &target, float t) const;
    Vector2D project(const Vector2D &onto) const;
    Vector2D reflect(const Vector2D &normal) const;
    Vector2D clamp_magnitude(float max_length) const;

    Vector2D perpendicular_left() const;
    Vector2D perpendicular_right() const;

    Vector2D operator+(const Vector2D &other) const;
    Vector2D &operator+=(const Vector2D &other);

    Vector2D operator-() const;
    Vector2D operator-(const Vector2D &other) const;
    Vector2D &operator-=(const Vector2D &other);

    Vector2D operator*(float scalar) const;
    Vector2D &operator*=(float scalar);

    friend Vector2D operator*(float scalar, const Vector2D &vector);

    Vector2D operator/(float scalar) const;
    Vector2D &operator/=(float scalar);

    Vector2D &operator=(const Vector3D &other);
    Vector2D &operator=(const Vector4D &other);

    bool operator==(const Vector2D &other) const;
    bool operator!=(const Vector2D &other) const;

    float x{};
    float y{};
};
