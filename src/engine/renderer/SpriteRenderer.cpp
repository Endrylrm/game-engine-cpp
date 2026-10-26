#include "engine/renderer/SpriteRenderer.hpp"

void SpriteRenderer::init(RenderDevice *new_device)
{
    device = new_device;
}

void SpriteRenderer::draw_texture(Texture *texture, Vector2D position)
{
    draw_texture(texture, Rect2D{position, texture->get_size()});
}

void SpriteRenderer::draw_texture(Texture *tex, Vector2D position, Vector2D size)
{
    draw_texture(tex, Rect2D{position, size});
}

void SpriteRenderer::draw_texture(Texture *tex, Rect2D rect)
{
    device->draw_texture(tex, rect);
}
