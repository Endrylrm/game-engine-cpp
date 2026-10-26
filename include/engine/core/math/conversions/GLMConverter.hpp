#pragma once
#include "engine/core/math/Math.hpp"
#include "engine/core/math/Matrix3.hpp"
#include "engine/core/math/Matrix4.hpp"
#include "engine/core/math/Quaternion.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/core/math/Vector3D.hpp"
#include "engine/core/math/Vector4D.hpp"

#include "GLMHeaders.hpp"

struct GLMConverter
{
    GLMConverter() = delete;

    static glm::vec2 to_glm(const Vector2D &vec);
    static Vector2D from_glm(const glm::vec2 &vec);

    static glm::vec3 to_glm(const Vector3D &vec);
    static Vector3D from_glm(const glm::vec3 &vec);

    static glm::vec4 to_glm(const Vector4D &vec);
    static Vector4D from_glm(const glm::vec4 &vec);

    static glm::quat to_glm(const Quaternion &quat);
    static Quaternion from_glm(const glm::quat &quat);

    static glm::mat3 to_glm(const Matrix3 &mat);
    static Matrix3 from_glm(const glm::mat3 &mat);

    static glm::mat4 to_glm(const Matrix4 &mat);
    static Matrix4 from_glm(const glm::mat4 &mat);
};
