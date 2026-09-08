#pragma once

class Vector4D
{
public:
    Vector4D() = default;
    Vector4D(float all) : x(all), y(all), z(all), w(all) {}
    Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    float x{};
    float y{};
    float z{};
    float w{};
};
