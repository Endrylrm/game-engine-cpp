#include "engine/renderer/SpriteRenderer.hpp"

void SpriteRenderer::init(RenderDevice *newDevice)
{
    device = newDevice;
}

void SpriteRenderer::drawTexture(Texture *texture, Vector2D position)
{
    drawTexture(texture, Rect2D{position, texture->getSize()});
}

void SpriteRenderer::drawTexture(Texture *tex, Vector2D position, Vector2D size)
{
    drawTexture(tex, Rect2D{position, size});
}

void SpriteRenderer::drawTexture(Texture *tex, Rect2D rect)
{
    device->drawTexture(tex, rect);
}
