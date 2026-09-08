#pragma once

class Vector2D
{
public:
    Vector2D() = default;
    Vector2D(float all) : x(all), y(all) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    static Vector2D Zero();
    static Vector2D One();
    static Vector2D Up();
    static Vector2D Down();
    static Vector2D Left();
    static Vector2D Right();

    float length() const;
    float lengthSquared() const;

    void normalize();
    Vector2D normalized() const;

    float distance(const Vector2D &other) const;
    float distanceSquared(const Vector2D &other) const;

    float dot(const Vector2D &other) const;
    float cross(const Vector2D &other) const;

    float angle() const;
    float angleDegrees() const;
    float angleTo(const Vector2D &other) const;

    Vector2D MoveTowards(const Vector2D &target, float maxDistanceDelta) const;
    Vector2D rotate(float radians) const;
    Vector2D lerp(const Vector2D &target, float t) const;
    Vector2D project(const Vector2D &onto) const;
    Vector2D reflect(const Vector2D &normal) const;
    Vector2D clampMagnitude(float maxLength) const;

    Vector2D perpendicularLeft() const;
    Vector2D perpendicularRight() const;

    Vector2D &operator+=(const Vector2D &other);
    Vector2D operator+(const Vector2D &other) const;

    Vector2D &operator-=(const Vector2D &other);
    Vector2D operator-(const Vector2D &other) const;

    Vector2D &operator*=(float scalar);
    Vector2D operator*(float scalar) const;

    Vector2D &operator/=(float scalar);
    Vector2D operator/(float scalar) const;

    float x{};
    float y{};
};
