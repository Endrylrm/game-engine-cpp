#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <cstdint>
#include "engine/core/graphics/Texture.hpp"

class SDLTexture : public Texture
{
public:
    SDLTexture(SDL_Renderer *renderer, const std::string &path);
    ~SDLTexture() override;

    void *getNativeHandle() const override;
    void bind(uint32_t slot = 0) const override;

    float getWidth() const override;
    float getHeight() const override;

    bool isValid() const override;

private:
    SDL_Texture *texture{};
    float width;
    float height;
};
