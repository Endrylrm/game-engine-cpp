#include "engine/core/math/conversions/GLMConverter.hpp"

glm::vec2 GLMConverter::to_glm(const Vector2D &vec)
{
    return {vec.x, vec.y};
}

Vector2D GLMConverter::from_glm(const glm::vec2 &vec)
{
    return {vec.x, vec.y};
}

glm::vec3 GLMConverter::to_glm(const Vector3D &vec)
{
    return {vec.x, vec.y, vec.z};
}

Vector3D GLMConverter::from_glm(const glm::vec3 &vec)
{
    return {vec.x, vec.y, vec.z};
}

glm::vec4 GLMConverter::to_glm(const Vector4D &vec)
{
    return {vec.x, vec.y, vec.z, vec.w};
}

Vector4D GLMConverter::from_glm(const glm::vec4 &vec)
{
    return {vec.x, vec.y, vec.z, vec.w};
}

glm::quat GLMConverter::to_glm(const Quaternion &quat)
{
    return {quat.x, quat.y, quat.z, quat.w};
}

Quaternion GLMConverter::from_glm(const glm::quat &quat)
{
    return {quat.x, quat.y, quat.z, quat.w};
}

glm::mat3 GLMConverter::to_glm(const Matrix3 &mat)
{
    glm::mat3 result{};

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            result[column][row] = mat[row][column];
        }
    }

    return result;
}

Matrix3 GLMConverter::from_glm(const glm::mat3 &mat)
{
    Matrix3 result{};

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            result[row][column] = mat[column][row];
        }
    }

    return result;
}

glm::mat4 GLMConverter::to_glm(const Matrix4 &mat)
{
    glm::mat4 result{};

    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            result[column][row] = mat[row][column];
        }
    }

    return result;
}

Matrix4 GLMConverter::from_glm(const glm::mat4 &mat)
{
    Matrix4 result{};

    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            result[row][column] = mat[column][row];
        }
    }

    return result;
}
