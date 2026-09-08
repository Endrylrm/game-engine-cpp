#pragma once
#define GLM_ENABLE_EXPERIMENTAL true
#include <algorithm>
#include <cmath>
#include <numbers>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Math
{
constexpr float EPSILON = 0.00001f;
constexpr float EPSILON_SQUARED = EPSILON * EPSILON;

constexpr bool approximatelyEqual(float a, float b)
{
    return std::abs(a - b) < EPSILON;
}

constexpr float PI = 3.14159265358979323846f;
constexpr float TAU = 2.0f * PI;

constexpr float radians(float degrees)
{
    return degrees * PI / 180.0f;
}

constexpr float degrees(float radians)
{
    return radians * 180.0f / PI;
}
} // namespace Math
