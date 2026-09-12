#pragma once
class Vector3D;

class Quaternion
{
public:
    constexpr Quaternion() : Quaternion(0.0f) {}
    constexpr Quaternion(float all) : Quaternion(all, all, all, all) {}
    constexpr Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static constexpr Quaternion identity();
    static Quaternion fromAxisAngle(const Vector3D &axis, float radians);
    static Quaternion fromEuler(float pitchX, float yawY, float rollZ);
    static Quaternion fromToRotation(const Vector3D &from, const Vector3D &to);

    Vector3D rotate(const Vector3D &vector) const;

    float lengthSquared() const;
    float length() const;

    Quaternion normalized() const;
    void normalize();

    Quaternion conjugate() const;

    Quaternion inverse() const;

    static float dot(const Quaternion &a, const Quaternion &b);

    void toAxisAngle(Vector3D &outAxis, float &outAngle) const;
    Vector3D toEuler() const;

    static Quaternion nlerp(const Quaternion &a, const Quaternion &b, float t);
    static Quaternion slerp(const Quaternion &a, const Quaternion &b, float t);

    Quaternion operator+(const Quaternion &other) const;
    Quaternion &operator+=(const Quaternion &other);

    Quaternion operator-(const Quaternion &other) const;
    Quaternion &operator-=(const Quaternion &other);
    Quaternion operator-() const;

    Quaternion operator*(const Quaternion &other) const;
    Quaternion &operator*=(const Quaternion &other);

    Quaternion operator*(float scalar) const;
    Quaternion &operator*=(float scalar);

    bool operator==(const Quaternion &other) const;
    bool operator!=(const Quaternion &other) const;

    float x{};
    float y{};
    float z{};
    float w{1.0f};
};
