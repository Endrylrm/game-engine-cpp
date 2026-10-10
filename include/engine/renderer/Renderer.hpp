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
    bool init(RenderDevice *newDevice);

    std::unique_ptr<Texture> loadTexture(const std::string &path);

    void drawTexture(Texture *texture, Vector2D position);
    void drawTexture(Texture *tex, Vector2D position, Vector2D size);
    void drawTexture(Texture *tex, Rect2D rect);
    void drawRect(Vector2D position, Vector2D size, Color color);
    void drawRect(Rect2D rect, Color color);

    void clear();
    void setClearColor(Color color);

    void present();

private:
    RenderDevice *device = nullptr;
    Color clearColor{0.0f, 0.0f, 0.0f, 1.0f};
};
