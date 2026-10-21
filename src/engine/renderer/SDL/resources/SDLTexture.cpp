#include "engine/renderer/SDL/resources/SDLTexture.hpp"

#include "engine/core/log/Log.hpp"

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

bool SDLTexture::isValid() const
{
    return texture != nullptr;
}

Vector2DInt SDLTexture::getSize() const
{
    return size;
}

SDL_Texture *SDLTexture::getNativeHandle() const
{
    return texture;
}
