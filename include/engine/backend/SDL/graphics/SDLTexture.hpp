#pragma once
#include <cstdint>
#include <string>

#include <SDL3/SDL.h>

#include <engine/core/graphics/Texture.hpp>
#include <engine/core/math/Vector2DInt.hpp>

class SDLTexture : public Texture
{
public:
    SDLTexture(SDL_Texture *texture, int width, int height);
    ~SDLTexture() override;

    SDL_Texture *getNativeHandle() const;

    Vector2DInt getSize() const override;

    bool isValid() const override;

private:
    SDL_Texture *texture{};
    Vector2DInt size{};
};
