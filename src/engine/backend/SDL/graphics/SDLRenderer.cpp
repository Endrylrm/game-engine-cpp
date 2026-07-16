#include "engine/backend/SDL/graphics/SDLRenderer.hpp"
#include "engine/backend/SDL/graphics/SDLTexture.hpp"

bool SDLRenderer::onInit(void *window)
{
    renderer = SDL_CreateRenderer(static_cast<SDL_Window *>(window), NULL);
    if (!renderer)
    {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    if (!TTF_Init())
    {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

std::unique_ptr<Texture> SDLRenderer::loadTexture(const std::string &path)
{
    return std::make_unique<SDLTexture>(renderer, path);
}

void SDLRenderer::drawTexture(Texture *texture, float x, float y)
{
    SDL_FRect dest{x, y, texture->getWidth(), texture->getHeight()};
    SDL_RenderTexture(renderer, static_cast<SDL_Texture *>(texture->getNativeHandle()), nullptr, &dest);
}

void SDLRenderer::drawTexture(Texture *texture, float x, float y, float w, float h)
{
    SDL_FRect dest{x, y, w, h};
    SDL_RenderTexture(renderer, static_cast<SDL_Texture *>(texture->getNativeHandle()), nullptr, &dest);
}

void SDLRenderer::drawTexture(Texture *texture, Rect2D rect)
{
    drawTexture(texture, rect.x, rect.y, rect.w, rect.h);
}

void SDLRenderer::drawRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
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

void *SDLRenderer::getNativeRenderer() const
{
    return renderer;
}

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
}
