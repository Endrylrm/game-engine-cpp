#pragma once
#include <engine/core/math/Math.hpp>
#include <engine/core/math/Quaternion.hpp>
#include <engine/core/math/Vector2D.hpp>
#include <engine/core/math/Vector3D.hpp>
#include <engine/core/math/Vector4D.hpp>

struct GLMConverter
{
    GLMConverter() = delete;

    static glm::vec2 toGLM(const Vector2D &vec);
    static Vector2D fromGLM(const glm::vec2 &vec);

    static glm::vec3 toGLM(const Vector3D &vec);
    static Vector3D fromGLM(const glm::vec3 &vec);

    static glm::vec4 toGLM(const Vector4D &vec);
    static Vector4D fromGLM(const glm::vec4 &vec);

    static glm::quat toGLM(const Quaternion &quat);
    static Quaternion fromGLM(const glm::quat &quat);
};
