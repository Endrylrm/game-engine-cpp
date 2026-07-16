#pragma once
#include "engine/entities/components/colliders/Collider.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/entities/components/Transform2D.hpp"
#include "engine/core/math/Circle.hpp"
#include "engine/core/math/Rect2D.hpp"
#include "engine/core/math/Vector2D.hpp"

class CircleCollider : public Collider
{
public:
    CircleCollider(float offsetX, float offsetY, float radius) : circle{offsetX, offsetY, radius} {}
    CircleCollider(Circle offsetCircle) : circle(offsetCircle) {}

    Rect2D GetAABB() const override
    {
        Vector2D offset = Vector2D{circle.x, circle.y};
        Vector2D position = owner->getComponent<Transform2D>()->position + offset;
        return {position.x - circle.r, position.y - circle.r, position.x + circle.r, position.y + circle.r};
    }

    Circle getCircle()
    {
        return circle;
    }

    void setCircle(float offsetX, float offsetY, float radius)
    {
        circle.x = offsetX;
        circle.y = offsetY;
        circle.r = radius;
    }

    void setCircle(Circle newCircle)
    {
        circle = std::move(newCircle);
    }

private:
    Circle circle;
};
