#pragma once
#include <memory>
#include <string>

#include "engine/core/math/Color.hpp"
#include "engine/renderer/RenderDevice.hpp"
#include "engine/renderer/resources/Texture.hpp"

#include "ShapeRenderer.hpp"
#include "SpriteRenderer.hpp"

class Renderer
{
public:
    bool init(RenderDevice *new_device);

    std::unique_ptr<Texture> load_texture(const std::string &path);

    ShapeRenderer &get_shape_renderer() noexcept;
    SpriteRenderer &get_sprite_renderer() noexcept;

    void clear();
    void set_clear_color(Color color);

    void present();

private:
    RenderDevice *device = nullptr;
    ShapeRenderer shape_renderer;
    SpriteRenderer sprite_renderer;
    Color clear_color{0.0f, 0.0f, 0.0f, 1.0f};
};
