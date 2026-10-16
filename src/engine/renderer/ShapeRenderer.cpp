#include "engine/renderer/ShapeRenderer.hpp"

void ShapeRenderer::init(RenderDevice *newDevice)
{
    device = newDevice;
}

void ShapeRenderer::drawRect(Vector2D position, Vector2D size, Color color)
{
    drawRect(Rect2D{position, size}, color);
}

void ShapeRenderer::drawRect(Rect2D rect, Color color)
{
    device->drawRect(rect, color);
}
