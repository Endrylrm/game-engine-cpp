#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "engine/core/math/Color.hpp"
#include "engine/core/math/Rect2D.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/renderer/RenderDevice.hpp"
#include "engine/renderer/resources/Texture.hpp"

class SDLDevice final : public RenderDevice
{
public:
    SDLDevice(SDL_Window *windowHandle);
    ~SDLDevice() override;

    bool init() override;
    void clear(Color color) override;
    void present() override;
    void set_viewport(Rect2D rect) override;

    std::unique_ptr<Texture> create_texture(const std::string &path) override;

    void draw_texture(Texture *texture, Rect2D rect) override;
    void draw_rect(Rect2D rect, Color color) override;

    SDL_Renderer *get_native_handle() const;

private:
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    TTF_Font *font{};
};
