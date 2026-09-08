#include "engine/core/math/conversions/GLMConverter.hpp"

glm::vec2 GLMConverter::toGLM(const Vector2D &vec)
{
    return {vec.x, vec.y};
}

Vector2D GLMConverter::fromGLM(const glm::vec2 &vec)
{
    return {vec.x, vec.y};
}

glm::vec3 GLMConverter::toGLM(const Vector3D &vec)
{
    return {vec.x, vec.y, vec.z};
}

Vector3D GLMConverter::fromGLM(const glm::vec3 &vec)
{
    return {vec.x, vec.y, vec.z};
}

glm::vec4 GLMConverter::toGLM(const Vector4D &vec)
{
    return {vec.x, vec.y, vec.z, vec.w};
}

Vector4D GLMConverter::fromGLM(const glm::vec4 &vec)
{
    return {vec.x, vec.y, vec.z, vec.w};
}

glm::quat GLMConverter::toGLM(const Quaternion &quat)
{
    return {quat.x, quat.y, quat.z, quat.w};
}

Quaternion GLMConverter::fromGLM(const glm::quat &quat)
{
    return {quat.x, quat.y, quat.z, quat.w};
}
