#pragma once
#include "engine/entities/components/colliders/Collider.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/core/math/Rect2D.hpp"
#include "engine/core/math/Vector2D.hpp"

class Rect2DCollider : public Collider
{
public:
    Rect2DCollider(float offsetX, float offsetY, float width, float height) : rect{offsetX, offsetY, width, height} {}
    Rect2DCollider(Rect2D offsetRect) : rect(offsetRect) {}

    Rect2D GetAABB() const override
    {
        Vector2D offset = Vector2D{rect.x, rect.y};
        Vector2D position = owner->getComponent<Transform2D>()->position + offset;
        return {position.x, position.y, position.x + rect.w, position.y + rect.h};
    }

    Rect2D getRect2D()
    {
        return rect;
    }

    void setRect2D(float offsetX, float offsetY, float width, float height)
    {
        rect.x = offsetX;
        rect.y = offsetY;
        rect.w = width;
        rect.h = height;
    }

    void setRect2D(Rect2D newRect)
    {
        rect = std::move(newRect);
    }

private:
    Rect2D rect;
};
