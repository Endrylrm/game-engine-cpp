#pragma once
#include "Vector2D.hpp"

struct Rect2D
{
    Rect2D() : Rect2D(0.0f) {}
    Rect2D(float all) : x(all), y(all), w(all), h(all) {}
    Rect2D(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    Rect2D(Vector2D position, Vector2D size) : Rect2D(position.x, position.y, size.x, size.y) {}

    float x{};
    float y{};
    float w{1.0f};
    float h{1.0f};

    Rect2D &operator+=(const Rect2D &other)
    {
        this->x += other.x;
        this->y += other.y;
        this->w += other.w;
        this->h += other.h;
        return *this;
    }

    Rect2D operator+(const Rect2D &other) const
    {
        Rect2D result = *this;
        result += other;
        return result;
    }

    Rect2D &operator-=(const Rect2D &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->w -= other.w;
        this->h -= other.h;
        return *this;
    }

    Rect2D operator-(const Rect2D &other) const
    {
        Rect2D result = *this;
        result -= other;
        return result;
    }

    Rect2D &operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->w *= scalar;
        this->h *= scalar;
        return *this;
    }

    Rect2D operator*(float scalar) const
    {
        Rect2D result = *this;
        result *= scalar;
        return result;
    }

    Rect2D &operator/=(float scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        this->w /= scalar;
        this->h /= scalar;
        return *this;
    }

    Rect2D operator/(float scalar) const
    {
        Rect2D result = *this;
        result /= scalar;
        return result;
    }
};
