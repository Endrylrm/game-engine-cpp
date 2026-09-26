#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <engine/core/math/Color.hpp>
#include <engine/core/math/Rect2D.hpp>
#include <engine/core/math/Vector2D.hpp>
#include <engine/renderer/Renderer.hpp>
#include <engine/renderer/resources/Texture.hpp>

class SDLRenderer final : public Renderer
{
public:
    SDLRenderer(SDL_Window *windowHandle);
    ~SDLRenderer() override;
    bool onInit() override;
    std::unique_ptr<Texture> loadTexture(const std::string &path) override;
    void drawTexture(Texture *texture, Vector2D position) override;
    void drawTexture(Texture *texture, Vector2D position, Vector2D size) override;
    void drawTexture(Texture *texture, Rect2D rect) override;
    void drawRect(Vector2D position, Vector2D size, Color color) override;
    void drawRect(Rect2D rect, Color color) override;
    void clear() override;
    void present() override;

    SDL_Renderer *getNativeHandle() const;

private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    TTF_Font *font{};
};
