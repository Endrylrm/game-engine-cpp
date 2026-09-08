#pragma once
class Vector2D;
class Vector3D;

class Vector4D
{
public:
    Vector4D() = default;
    Vector4D(float all) : x(all), y(all), z(all), w(all) {}
    Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4D(const Vector4D &other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
    Vector4D(Vector2D vec);
    Vector4D(Vector3D vec);

    float length() const;
    float lengthSquared() const;

    Vector4D normalized() const;
    void normalize();

    float dot(const Vector4D &other) const;

    Vector4D operator+(const Vector4D &other) const;
    Vector4D &operator+=(const Vector4D &other);

    Vector4D operator-(const Vector4D &other) const;
    Vector4D &operator-=(const Vector4D &other);

    Vector4D operator*(float scalar) const;
    Vector4D &operator*=(float scalar);

    Vector4D operator/(float scalar) const;
    Vector4D &operator/=(float scalar);

    Vector4D &operator=(const Vector2D &other);
    Vector4D &operator=(const Vector3D &other);

    bool operator==(const Vector4D &other) const;
    bool operator!=(const Vector4D &other) const;

    float x{};
    float y{};
    float z{};
    float w{};
};
