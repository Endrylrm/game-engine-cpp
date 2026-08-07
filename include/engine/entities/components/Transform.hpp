#pragma once
#include <engine/core/math/Vector2D.hpp>

class Transform
{
public:
    Transform() = default;
    Transform(Vector2D position) : position(position) {}
    Transform(Vector2D position, float rotation) : position(position), rotation(rotation) {}
    Transform(Vector2D position, float rotation, Vector2D scale)
        : position(position), rotation(rotation), scale(scale)
    {
    }
    Transform(float positionX, float positionY) : position{positionX, positionY} {}
    Transform(float positionX, float positionY, float rotation)
        : position{positionX, positionY}, rotation(rotation)
    {
    }
    Transform(float positionX, float positionY, float rotation, float scaleX, float scaleY)
        : position{positionX, positionY}, rotation(rotation), scale{scaleX, scaleY}
    {
    }

    ~Transform() = default;

    Vector2D position{};
    float rotation{};
    Vector2D scale{Vector2D::One()};
};
