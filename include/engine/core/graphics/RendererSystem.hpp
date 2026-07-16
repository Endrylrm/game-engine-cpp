#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include "engine/core/math/Rect2D.hpp"
#include "engine/core/graphics/Texture.hpp"

class RendererSystem
{
public:
    virtual ~RendererSystem() = default;

    virtual bool onInit(void *window) = 0;
    virtual std::unique_ptr<Texture> loadTexture(const std::string &path) = 0;
    virtual void drawTexture(Texture *texture, float x, float y) = 0;
    virtual void drawTexture(Texture *texture, float x, float y, float w, float h) = 0;
    virtual void drawTexture(Texture *texture, Rect2D rect) = 0;
    virtual void drawRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) = 0;
    virtual void drawRect(Rect2D rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) = 0;
    virtual void clear() = 0;
    virtual void present() = 0;

    virtual void *getNativeRenderer() const = 0;
};
