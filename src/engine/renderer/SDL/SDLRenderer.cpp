#include "engine/renderer/SDL/SDLRenderer.hpp"

#include <SDL3_image/SDL_image.h>

#include <engine/core/log/Log.hpp>
#include <engine/renderer/SDL/resources/SDLTexture.hpp>

SDLRenderer::SDLRenderer(SDL_Window *windowHandle) : window(windowHandle) {}

SDLRenderer::~SDLRenderer()
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

bool SDLRenderer::onInit()
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

std::unique_ptr<Texture> SDLRenderer::loadTexture(const std::string &path)
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

void SDLRenderer::drawTexture(Texture *texture, Vector2D position)
{
    drawTexture(texture, position, texture->getSize());
}

void SDLRenderer::drawTexture(Texture *texture, Vector2D position, Vector2D size)
{
    auto *sdlTexture = static_cast<SDLTexture *>(texture);
    SDL_FRect dest{position.x, position.y, size.x, size.y};
    SDL_Texture *handle = sdlTexture->getNativeHandle();
    SDL_RenderTexture(renderer, handle, nullptr, &dest);
}

void SDLRenderer::drawTexture(Texture *texture, Rect2D rect)
{
    drawTexture(texture, Vector2D{rect.x, rect.y}, Vector2D{rect.w, rect.h});
}

void SDLRenderer::drawRect(Vector2D position, Vector2D size, Color color)
{
    RGBA32 rgbaColor = color.toRGBA32();
    SDL_SetRenderDrawColor(renderer, rgbaColor.r, rgbaColor.g, rgbaColor.b, rgbaColor.a);
    SDL_FRect dest{position.x, position.y, size.x, size.y};
    SDL_RenderFillRect(renderer, &dest);
}

void SDLRenderer::drawRect(Rect2D rect, Color color)
{
    drawRect(Vector2D{rect.x, rect.y}, Vector2D{rect.w, rect.h}, color);
}

void SDLRenderer::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDLRenderer::present()
{
    SDL_RenderPresent(renderer);
}

SDL_Renderer *SDLRenderer::getNativeHandle() const
{
    return renderer;
}
