#include "engine/backend/SDL/graphics/SDLTexture.hpp"

#include <SDL3_image/SDL_image.h>
#include <stdexcept>

#include "engine/core/log/Log.hpp"

SDLTexture::SDLTexture(SDL_Renderer *renderer, const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface)
    {
        LOG_ERROR("Unable to create surface: {}", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    width = static_cast<float>(surface->w);
    height = static_cast<float>(surface->h);

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_DestroySurface(surface);

    if (!texture)
    {
        LOG_ERROR("Unable to create texture: {}", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    LOG_DEBUG("SDL Texture Created.");
}

void SDLTexture::bind(uint32_t slot /* = 0 */) const {}

bool SDLTexture::isValid() const
{
    return texture != nullptr;
}

void *SDLTexture::getNativeHandle() const
{
    return texture;
}

float SDLTexture::getWidth() const
{
    return width;
}

float SDLTexture::getHeight() const
{
    return height;
}

SDLTexture::~SDLTexture()
{
    SDL_DestroyTexture(texture);
    LOG_DEBUG("SDL Texture Destroyed.");
}