#include "engine/renderer/Renderer.hpp"

#include "engine/core/math/Rect2D.hpp"

bool Renderer::init(RenderDevice *new_device)
{
    device = new_device;

    if (!device->init())
        return false;

    shape_renderer.init(device);
    sprite_renderer.init(device);

    device->set_viewport(Rect2D{0.0f, 0.0f, 800.0f, 600.0f});
    return true;
}

std::unique_ptr<Texture> Renderer::load_texture(const std::string &path)
{
    return device->create_texture(path);
}

ShapeRenderer &Renderer::get_shape_renderer() noexcept
{
    return shape_renderer;
}

SpriteRenderer &Renderer::get_sprite_renderer() noexcept
{
    return sprite_renderer;
}

void Renderer::clear()
{
    device->clear(clear_color);
}

void Renderer::set_clear_color(Color color)
{
    clear_color = color;
}

void Renderer::present()
{
    device->present();
}
