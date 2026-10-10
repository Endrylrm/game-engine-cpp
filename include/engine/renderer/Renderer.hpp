#pragma once
#include <cstdint>
#include <memory>
#include <string>

#include <engine/core/math/Color.hpp>
#include <engine/core/math/Rect2D.hpp>
#include <engine/core/math/Vector2D.hpp>
#include <engine/renderer/RenderDevice.hpp>
#include <engine/renderer/resources/Texture.hpp>

class Renderer
{
public:
    bool init(RenderDevice *newDevice)
    {
        device = newDevice;
        return device->init();
    }

    std::unique_ptr<Texture> loadTexture(const std::string &path)
    {
        return device->createTexture(path);
    }

    void drawTexture(Texture *texture, Vector2D position)
    {
        drawTexture(texture, Rect2D{position, texture->getSize()});
    }

    void drawTexture(Texture *tex, Vector2D position, Vector2D size)
    {
        drawTexture(tex, Rect2D{position, size});
    }

    void drawTexture(Texture *tex, Rect2D rect)
    {
        device->drawTexture(tex, rect);
    }

    void drawRect(Vector2D position, Vector2D size, Color color)
    {
        drawRect(Rect2D{position, size}, color);
    }

    void drawRect(Rect2D rect, Color color)
    {
        device->drawRect(rect, color);
    }

    void clear()
    {
        device->clear(clearColor);
    }

    void present()
    {
        device->present();
    }

    void setClearColor(Color color)
    {
        clearColor = color;
    }

private:
    RenderDevice *device = nullptr;
    Color clearColor{0.0f, 0.0f, 0.0f, 1.0f};
};
