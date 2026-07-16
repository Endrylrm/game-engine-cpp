#pragma once
#include "engine/core/math/Vector2D.hpp"

class Transform2D
{
public:
    Transform2D() = default;
    Transform2D(Vector2D position) : position(position) {}
    Transform2D(Vector2D position, float rotation) : position(position), rotation(rotation) {}
    Transform2D(Vector2D position, float rotation, Vector2D scale) : position(position), rotation(rotation), scale(scale) {}
    Transform2D(float positionX, float positionY) : position{positionX, positionY} {}
    Transform2D(float positionX, float positionY, float rotation) : position{positionX, positionY}, rotation(rotation) {}
    Transform2D(float positionX, float positionY, float rotation, float scaleX, float scaleY) : position{positionX, positionY}, rotation(rotation), scale{scaleX, scaleY} {}
    ~Transform2D() = default;

    Vector2D position{0.0f, 0.0f};
    float rotation{0.0f};
    Vector2D scale{1.0f, 1.0f};
};
