#include "engine/backend/SDL/graphics/SDLTexture.hpp"

#include <engine/core/log/Log.hpp>

SDLTexture::SDLTexture(SDL_Texture *texture, int width, int height)
    : texture(texture), width(width), height(height)
{
}

SDLTexture::~SDLTexture()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        LOG_DEBUG("SDL Texture Destroyed.");
    }
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
