#pragma once
#include <algorithm>
#include <cmath>
#include <numbers>

namespace Math
{
// constants
constexpr float EPSILON = 0.00001f;
constexpr float EPSILON_SQUARED = EPSILON * EPSILON;

constexpr float PI = 3.14159265358979323846f;
constexpr float TAU = 2.0f * PI;

// float comparison
constexpr bool approximatelyEqual(float a, float b)
{
    return std::abs(a - b) < EPSILON;
}

constexpr bool approximatelyZero(float value)
{
    return std::abs(value) < EPSILON;
}

// Angles
constexpr float radians(float degrees)
{
    return degrees * PI / 180.0f;
}

constexpr float degrees(float radians)
{
    return radians * 180.0f / PI;
}

// General
constexpr float clamp(float value, float min, float max)
{
    return value < min ? min : value > max ? max : value;
}

constexpr float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

constexpr float inverseLerp(float a, float b, float value)
{
    return (value - a) / (b - a);
}

constexpr float square(float value)
{
    return value * value;
}
} // namespace Math
