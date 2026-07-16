#pragma once
#include <cmath>
#include <numbers>
#include <algorithm>
#include "engine/core/math/Math.hpp"
#include "engine/core/math/Vector3D.hpp"
#include "engine/core/math/Quaternion.hpp"

class Matrix4;

class Matrix3
{
public:
    float m[9];

    constexpr Matrix3()
        : m{1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f}
    {
    }

    constexpr Matrix3(float m00, float m01, float m02,
                      float m10, float m11, float m12,
                      float m20, float m21, float m22)
        : m{m00, m10, m20,
            m01, m11, m21,
            m02, m12, m22}
    {
    }

    static constexpr Matrix3 identity()
    {
        return Matrix3();
    }

    static Matrix3 scale(const Vector3D &s)
    {
        Matrix3 r;
        r(0, 0) = s.x;
        r(1, 1) = s.y;
        r(2, 2) = s.z;
        return r;
    }

    static Matrix3 scale(float uniform) { return scale(Vector3D(uniform, uniform, uniform)); }

    static Matrix3 rotationZ(float radians)
    {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        Matrix3 r;
        r(0, 0) = c;
        r(0, 1) = -s;
        r(1, 0) = s;
        r(1, 1) = c;
        return r;
    }

    static Matrix3 rotationX(float radians)
    {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        Matrix3 r;
        r(1, 1) = c;
        r(1, 2) = -s;
        r(2, 1) = s;
        r(2, 2) = c;
        return r;
    }

    static Matrix3 rotationY(float radians)
    {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        Matrix3 r;
        r(0, 0) = c;
        r(0, 2) = s;
        r(2, 0) = -s;
        r(2, 2) = c;
        return r;
    }

    static Matrix3 fromQuaternion(const Quaternion &q)
    {
        return fromGLM(glm::mat3_cast(q.toGLM()));
    }

    static Matrix3 fromMatrix4(const Matrix4 &m4);
    static Matrix3 normalMatrix(const Matrix4 &modelMatrix);

    float &operator()(int row, int col) { return m[col * 3 + row]; }
    float operator()(int row, int col) const { return m[col * 3 + row]; }

    const float *data() const { return m; }

    Matrix3 operator*(const Matrix3 &rhs) const
    {
        Matrix3 result;
        for (int col = 0; col < 3; ++col)
        {
            for (int row = 0; row < 3; ++row)
            {
                float sum = 0.0f;
                for (int k = 0; k < 3; ++k)
                    sum += (*this)(row, k) * rhs(k, col);
                result(row, col) = sum;
            }
        }
        return result;
    }

    Vector3D operator*(const Vector3D &v) const
    {
        return Vector3D(
            (*this)(0, 0) * v.x + (*this)(0, 1) * v.y + (*this)(0, 2) * v.z,
            (*this)(1, 0) * v.x + (*this)(1, 1) * v.y + (*this)(1, 2) * v.z,
            (*this)(2, 0) * v.x + (*this)(2, 1) * v.y + (*this)(2, 2) * v.z);
    }

    bool operator==(const Matrix3 &o) const
    {
        for (int i = 0; i < 9; ++i)
            if (m[i] != o.m[i])
                return false;
        return true;
    }

    Matrix3 transposed() const
    {
        Matrix3 r;
        for (int col = 0; col < 3; ++col)
            for (int row = 0; row < 3; ++row)
                r(row, col) = (*this)(col, row);
        return r;
    }

    float determinant() const
    {
        return (*this)(0, 0) * ((*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1)) - (*this)(0, 1) * ((*this)(1, 0) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 0)) + (*this)(0, 2) * ((*this)(1, 0) * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0));
    }

    Matrix3 inverse() const
    {
        const float det = determinant();
        if (std::abs(det) < 1e-8f)
            return identity();

        const float invDet = 1.0f / det;
        Matrix3 r;

        r(0, 0) = ((*this)(1, 1) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 1)) * invDet;
        r(0, 1) = -((*this)(0, 1) * (*this)(2, 2) - (*this)(0, 2) * (*this)(2, 1)) * invDet;
        r(0, 2) = ((*this)(0, 1) * (*this)(1, 2) - (*this)(0, 2) * (*this)(1, 1)) * invDet;

        r(1, 0) = -((*this)(1, 0) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 0)) * invDet;
        r(1, 1) = ((*this)(0, 0) * (*this)(2, 2) - (*this)(0, 2) * (*this)(2, 0)) * invDet;
        r(1, 2) = -((*this)(0, 0) * (*this)(1, 2) - (*this)(0, 2) * (*this)(1, 0)) * invDet;

        r(2, 0) = ((*this)(1, 0) * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0)) * invDet;
        r(2, 1) = -((*this)(0, 0) * (*this)(2, 1) - (*this)(0, 1) * (*this)(2, 0)) * invDet;
        r(2, 2) = ((*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0)) * invDet;

        return r;
    }

private:
    glm::mat3 toGLM() const { return glm::make_mat3(m); }
    static Matrix3 fromGLM(const glm::mat3 &g)
    {
        Matrix3 r;
        std::memcpy(r.m, glm::value_ptr(g), sizeof(r.m));
        return r;
    }
};