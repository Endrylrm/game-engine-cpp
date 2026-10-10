#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <engine/core/math/Color.hpp>
#include <engine/core/math/Rect2D.hpp>
#include <engine/core/math/Vector2D.hpp>
#include <engine/renderer/RenderDevice.hpp>
#include <engine/renderer/resources/Texture.hpp>

class SDLDevice final : public RenderDevice
{
public:
    SDLDevice(SDL_Window *windowHandle);
    ~SDLDevice() override;

    bool init() override;
    void clear(Color color) override;
    void present() override;

    std::unique_ptr<Texture> createTexture(const std::string &path) override;

    void drawTexture(Texture *texture, Rect2D rect) override;
    void drawRect(Rect2D rect, Color color) override;

    SDL_Renderer *getNativeHandle() const;

private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    TTF_Font *font{};
};
