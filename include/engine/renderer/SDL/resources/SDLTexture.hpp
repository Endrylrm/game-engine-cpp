#pragma once
#include <cstdint>
#include <string>

#include <SDL3/SDL.h>

#include "engine/core/math/Vector2DInt.hpp"
#include "engine/renderer/resources/Texture.hpp"

class SDLTexture final : public Texture
{
public:
    SDLTexture(SDL_Texture *texture, int width, int height);
    ~SDLTexture() override;

    bool isValid() const override;

    Vector2DInt getSize() const override;
    SDL_Texture *get_native_handle() const;

private:
    SDL_Texture *texture{};
    Vector2DInt size{};
};
