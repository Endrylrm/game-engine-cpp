#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <memory>
#include <unordered_map>
#include "engine/core/graphics/Renderer.hpp"
#include "engine/core/graphics/Texture.hpp"
#include "engine/core/math/Rect2D.hpp"

class SDLRenderer : public Renderer
{
public:
    ~SDLRenderer() override;
    bool onInit(void *window) override;
    std::unique_ptr<Texture> loadTexture(const std::string &path) override;
    void drawTexture(Texture *texture, float x, float y) override;
    void drawTexture(Texture *texture, float x, float y, float w, float h) override;
    void drawTexture(Texture *texture, Rect2D rect) override;
    void drawRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void drawRect(Rect2D rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void clear() override;
    void present() override;

    void *getNativeRenderer() const override;

private:
    SDL_Renderer *renderer{};
    TTF_Font *font{};
};
