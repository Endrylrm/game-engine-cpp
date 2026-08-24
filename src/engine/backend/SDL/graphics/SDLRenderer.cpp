#include "engine/backend/SDL/graphics/SDLRenderer.hpp"

#include <SDL3_image/SDL_image.h>

#include <engine/backend/SDL/graphics/SDLTexture.hpp>
#include <engine/core/log/Log.hpp>

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

void SDLRenderer::drawTexture(Texture *texture, float x, float y)
{
    drawTexture(
        texture,
        x,
        y,
        static_cast<float>(texture->getWidth()),
        static_cast<float>(texture->getHeight())
    );
}

void SDLRenderer::drawTexture(Texture *texture, float x, float y, float w, float h)
{
    auto *sdlTexture = static_cast<SDLTexture *>(texture);
    SDL_FRect dest{x, y, w, h};
    SDL_Texture *handle = sdlTexture->getNativeHandle();
    SDL_RenderTexture(renderer, handle, nullptr, &dest);
}

void SDLRenderer::drawTexture(Texture *texture, Rect2D rect)
{
    drawTexture(texture, rect.x, rect.y, rect.w, rect.h);
}

void SDLRenderer::drawRect(
    float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a
)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_FRect rectangle{x, y, w, h};
    SDL_RenderFillRect(renderer, &rectangle);
}

void SDLRenderer::drawRect(Rect2D rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    drawRect(rect.x, rect.y, rect.w, rect.h, r, g, b, a);
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
