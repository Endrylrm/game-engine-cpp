#include "engine/backend/SDL/graphics/SDLTexture.hpp"

#include <engine/core/log/Log.hpp>

SDLTexture::SDLTexture(SDL_Texture *texture, int width, int height)
    : texture(texture), size(width, height)
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

SDL_Texture *SDLTexture::getNativeHandle() const
{
    return texture;
}

Vector2DInt SDLTexture::getSize() const
{
    return size;
}

bool SDLTexture::isValid() const
{
    return texture != nullptr;
}
