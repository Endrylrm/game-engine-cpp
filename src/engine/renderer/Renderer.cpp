#include "engine/renderer/Renderer.hpp"

bool Renderer::init(RenderDevice *newDevice)
{
    device = newDevice;

    if (!device->init())
        return false;

    device->setViewport(Rect2D{0.0f, 0.0f, 800.0f, 600.0f});
    return true;
}

std::unique_ptr<Texture> Renderer::loadTexture(const std::string &path)
{
    return device->createTexture(path);
}

void Renderer::drawTexture(Texture *texture, Vector2D position)
{
    drawTexture(texture, Rect2D{position, texture->getSize()});
}

void Renderer::drawTexture(Texture *tex, Vector2D position, Vector2D size)
{
    drawTexture(tex, Rect2D{position, size});
}

void Renderer::drawTexture(Texture *tex, Rect2D rect)
{
    device->drawTexture(tex, rect);
}

void Renderer::drawRect(Vector2D position, Vector2D size, Color color)
{
    drawRect(Rect2D{position, size}, color);
}

void Renderer::drawRect(Rect2D rect, Color color)
{
    device->drawRect(rect, color);
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
