#pragma once
#include <cstdint>
#include <memory>
#include <string>

#include <engine/core/math/Color.hpp>
#include <engine/core/math/Rect2D.hpp>
#include <engine/core/math/Vector2D.hpp>
#include <engine/renderer/resources/Texture.hpp>

class Renderer
{
public:
    virtual ~Renderer() = default;

    virtual bool onInit() = 0;
    virtual std::unique_ptr<Texture> loadTexture(const std::string &path) = 0;
    virtual void drawTexture(Texture *texture, Vector2D position) = 0;
    virtual void drawTexture(Texture *texture, Vector2D position, Vector2D size) = 0;
    virtual void drawTexture(Texture *texture, Rect2D rect) = 0;
    virtual void drawRect(Vector2D position, Vector2D size, Color color) = 0;
    virtual void drawRect(Rect2D rect, Color color) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;
};
