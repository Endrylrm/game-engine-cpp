#pragma once

struct Rect2D
{
    float x = 0;
    float y = 0;
    float w = 1;
    float h = 1;

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
