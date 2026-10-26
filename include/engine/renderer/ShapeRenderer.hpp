#pragma once
#include "engine/core/math/Color.hpp"
#include "engine/core/math/Rect2D.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/renderer/RenderDevice.hpp"

class ShapeRenderer
{
public:
    void init(RenderDevice *new_device);

    void draw_rect(Vector2D position, Vector2D size, Color color);
    void draw_rect(Rect2D rect, Color color);

private:
    RenderDevice *device = nullptr;
};
