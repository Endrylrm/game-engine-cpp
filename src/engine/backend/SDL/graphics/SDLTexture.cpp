#include "engine/backend/SDL/graphics/SDLTexture.hpp"

#include <stdexcept>

#include <SDL3_image/SDL_image.h>

#include <engine/core/log/Log.hpp>

SDLTexture::SDLTexture(SDL_Renderer *renderer, const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface)
    {
        LOG_ERROR("Unable to create surface: {}", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    width = surface->w;
    height = surface->h;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_DestroySurface(surface);

    if (!texture)
    {
        LOG_ERROR("Unable to create texture: {}", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }

    LOG_DEBUG("SDL Texture Created.");
}

bool SDLTexture::isValid() const
{
    return texture != nullptr;
}

SDL_Texture *SDLTexture::getNativeHandle() const
{
    return texture;
}

int SDLTexture::getWidth() const
{
    return width;
}

int SDLTexture::getHeight() const
{
    return height;
}

SDLTexture::~SDLTexture()
{
    SDL_DestroyTexture(texture);
    LOG_DEBUG("SDL Texture Destroyed.");
}