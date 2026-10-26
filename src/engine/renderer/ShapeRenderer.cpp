#include "engine/renderer/ShapeRenderer.hpp"

void ShapeRenderer::init(RenderDevice *new_device)
{
    device = new_device;
}

void ShapeRenderer::draw_rect(Vector2D position, Vector2D size, Color color)
{
    draw_rect(Rect2D{position, size}, color);
}

void ShapeRenderer::draw_rect(Rect2D rect, Color color)
{
    device->draw_rect(rect, color);
}
