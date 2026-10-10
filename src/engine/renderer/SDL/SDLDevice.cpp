#include "engine/renderer/SDL/SDLDevice.hpp"

#include <SDL3_image/SDL_image.h>

#include <engine/core/log/Log.hpp>
#include <engine/renderer/SDL/resources/SDLTexture.hpp>

SDLDevice::SDLDevice(SDL_Window *windowHandle) : window(windowHandle) {}

SDLDevice::~SDLDevice()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
    TTF_Quit();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    LOG_DEBUG("SDL Renderer destroyed.");
}

bool SDLDevice::init()
{
    renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        LOG_ERROR("Failed to create Renderer: {}", SDL_GetError());
        return false;
    }

    if (!TTF_Init())
    {
        LOG_ERROR("Couldn't initialize SDL_ttf: {}", SDL_GetError());
        return false;
    }

    LOG_DEBUG("SDL Renderer Initialized.");
    return true;
}

std::unique_ptr<Texture> SDLDevice::createTexture(const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface)
    {
        LOG_ERROR("Unable to create surface: {}", SDL_GetError());
        return nullptr;
    }

    int width = surface->w;
    int height = surface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_DestroySurface(surface);

    if (!texture)
    {
        LOG_ERROR("Unable to create texture: {}", SDL_GetError());
        return nullptr;
    }

    LOG_DEBUG("SDL Texture Created.");

    return std::make_unique<SDLTexture>(texture, width, height);
}

void SDLDevice::drawTexture(Texture *texture, Rect2D rect)
{
    auto *sdlTexture = static_cast<SDLTexture *>(texture);
    SDL_FRect dest{rect.x, rect.y, rect.w, rect.h};
    SDL_Texture *handle = sdlTexture->getNativeHandle();
    SDL_RenderTexture(renderer, handle, nullptr, &dest);
}

void SDLDevice::drawRect(Rect2D rect, Color color)
{
    RGBA32 rgbaColor = color.toRGBA32();
    SDL_SetRenderDrawColor(renderer, rgbaColor.r, rgbaColor.g, rgbaColor.b, rgbaColor.a);
    SDL_FRect dest{rect.x, rect.y, rect.w, rect.h};
    SDL_RenderFillRect(renderer, &dest);
}

void SDLDevice::clear(Color color)
{
    RGBA32 rgbaColor = color.toRGBA32();
    SDL_SetRenderDrawColor(renderer, rgbaColor.r, rgbaColor.g, rgbaColor.b, rgbaColor.a);
    SDL_RenderClear(renderer);
}

void SDLDevice::present()
{
    SDL_RenderPresent(renderer);
}

void SDLDevice::setViewport(Rect2D rect)
{
    SDL_FRect viewport = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderSetViewport(renderer, &viewport);
}

SDL_Renderer *SDLDevice::getNativeHandle() const
{
    return renderer;
}
