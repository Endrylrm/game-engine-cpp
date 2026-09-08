#pragma once
class Vector2D;
class Vector4D;

class Vector3D
{
public:
    Vector3D() = default;
    Vector3D(float all) : x(all), y(all), z(all) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D &other) : x(other.x), y(other.y), z(other.z) {}
    Vector3D(Vector2D vec);
    Vector3D(Vector4D vec);

    static Vector3D Zero();
    static Vector3D One();
    static Vector3D Up();
    static Vector3D Down();
    static Vector3D Left();
    static Vector3D Right();
    static Vector3D Forward();
    static Vector3D Back();

    bool isZero() const;

    float length() const;
    float lengthSquared() const;

    void normalize();
    Vector3D normalized() const;

    float distance(const Vector3D &other) const;
    float distanceSquared(const Vector3D &other) const;

    float dot(const Vector3D &other) const;
    Vector3D cross(const Vector3D &other) const;

    float angle(const Vector3D &other) const;
    float angleDegrees(const Vector3D &other) const;

    float pitch() const;
    float pitchDegrees() const;

    float yaw() const;
    float yawDegrees() const;

    Vector3D moveTowards(const Vector3D &target, float maxDistanceDelta) const;
    Vector3D rotateTowards(const Vector3D &target, float maxRadiansDelta) const;
    Vector3D lerp(const Vector3D &target, float t) const;
    Vector3D project(const Vector3D &onto) const;
    Vector3D reflect(const Vector3D &normal) const;
    Vector3D clampMagnitude(float maxLength) const;
    Vector3D perpendicular() const;

    Vector3D operator+(const Vector3D &other) const;
    Vector3D &operator+=(const Vector3D &other);

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
