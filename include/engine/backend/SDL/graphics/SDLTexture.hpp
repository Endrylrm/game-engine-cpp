#pragma once
#include <cstdint>
#include <string>

#include <SDL3/SDL.h>

#include <engine/core/graphics/Texture.hpp>

class SDLTexture : public Texture
{
public:
    SDLTexture(SDL_Renderer *renderer, const std::string &path);
    ~SDLTexture() override;

    SDL_Texture *getNativeHandle() const;

    int getWidth() const override;
    int getHeight() const override;

    bool isValid() const override;

private:
    SDL_Texture *texture{};
    int width;
    int height;
};
