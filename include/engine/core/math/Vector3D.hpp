#pragma once
class Vector2D;
class Vector4D;

class Vector3D
{
public:
    Vector3D() : Vector3D(0.0f) {}
    Vector3D(float all) : Vector3D(all, all, all) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D &other) : Vector3D(other.x, other.y, other.z) {}
    Vector3D(Vector2D vec);
    Vector3D(Vector2D vec, float z);
    Vector3D(Vector4D vec);

    static Vector3D zero();
    static Vector3D one();
    static Vector3D up();
    static Vector3D down();
    static Vector3D left();
    static Vector3D right();
    static Vector3D forward();
    static Vector3D back();

    bool is_zero() const;

    float length() const;
    float length_squared() const;

    void normalize();
    Vector3D normalized() const;

    float distance(const Vector3D &other) const;
    float distance_squared(const Vector3D &other) const;

    float dot(const Vector3D &other) const;
    Vector3D cross(const Vector3D &other) const;

    float angle(const Vector3D &other) const;
    float angle_degrees(const Vector3D &other) const;

    float pitch() const;
    float pitch_degrees() const;

    float yaw() const;
    float yaw_degrees() const;

    Vector3D move_towards(const Vector3D &target, float max_distance_delta) const;
    Vector3D rotate_towards(const Vector3D &target, float max_radians_delta) const;
    Vector3D lerp(const Vector3D &target, float t) const;
    Vector3D project(const Vector3D &onto) const;
    Vector3D reflect(const Vector3D &normal) const;
    Vector3D clamp_magnitude(float max_length) const;
    Vector3D perpendicular() const;

    Vector3D operator+(const Vector3D &other) const;
    Vector3D &operator+=(const Vector3D &other);

    Vector3D operator-() const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D &operator-=(const Vector3D &other);

    Vector3D operator*(float scalar) const;
    Vector3D &operator*=(float scalar);

    friend Vector3D operator*(float scalar, const Vector3D &vector);

    Vector3D operator*(const Vector3D &other) const;
    Vector3D &operator*=(const Vector3D &other);

    Vector3D operator/(float scalar) const;
    Vector3D &operator/=(float scalar);

    Vector3D &operator=(const Vector2D &other);
    Vector3D &operator=(const Vector4D &other);

    bool operator==(const Vector3D &other) const;
    bool operator!=(const Vector3D &other) const;

    float x{};
    float y{};
    float z{};
};
