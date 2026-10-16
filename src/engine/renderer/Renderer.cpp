#include "engine/renderer/Renderer.hpp"

#include <engine/core/math/Rect2D.hpp>

bool Renderer::init(RenderDevice *newDevice)
{
    device = newDevice;

    if (!device->init())
        return false;

    shapeRenderer.init(device);
    spriteRenderer.init(device);

    device->setViewport(Rect2D{0.0f, 0.0f, 800.0f, 600.0f});
    return true;
}

std::unique_ptr<Texture> Renderer::loadTexture(const std::string &path)
{
    return device->createTexture(path);
}

ShapeRenderer &Renderer::getShapeRenderer() noexcept
{
    return shapeRenderer;
}

SpriteRenderer &Renderer::getSpriteRenderer() noexcept
{
    return spriteRenderer;
}

void Renderer::clear()
{
    device->clear(clearColor);
}

void Renderer::setClearColor(Color color)
{
    clearColor = color;
}

void Renderer::present()
{
    device->present();
}
