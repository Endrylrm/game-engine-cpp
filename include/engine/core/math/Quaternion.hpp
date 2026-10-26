#pragma once
class Vector3D;

class Quaternion
{
public:
    constexpr Quaternion() : Quaternion(0.0f) {}
    constexpr Quaternion(float all) : Quaternion(all, all, all, all) {}
    constexpr Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    inline static constexpr Quaternion identity()
    {
        return Quaternion{0.0f, 0.0f, 0.0f, 1.0f};
    }

    static Quaternion from_axis_angle(const Vector3D &axis, float radians);
    static Quaternion from_euler(float pitch_x, float yaw_y, float roll_z);
    static Quaternion from_to_rotation(const Vector3D &from, const Vector3D &to);

    Vector3D rotate(const Vector3D &vector) const;

    float length_squared() const;
    float length() const;

    Quaternion normalized() const;
    void normalize();

    Quaternion conjugate() const;

    Quaternion inverse() const;

    static float dot(const Quaternion &a, const Quaternion &b);

    void to_axis_angle(Vector3D &out_axis, float &out_angle) const;
    Vector3D to_euler() const;

    static Quaternion nlerp(const Quaternion &a, const Quaternion &b, float t);
    static Quaternion slerp(const Quaternion &a, const Quaternion &b, float t);

    Quaternion operator+(const Quaternion &other) const;
    Quaternion &operator+=(const Quaternion &other);

    Quaternion operator-() const;
    Quaternion operator-(const Quaternion &other) const;
    Quaternion &operator-=(const Quaternion &other);

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
