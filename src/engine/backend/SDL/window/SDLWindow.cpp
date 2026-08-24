#include "engine/backend/SDL/window/SDLWindow.hpp"

#include <engine/core/log/Log.hpp>

SDLWindow::SDLWindow(std::string newTitle, int newWidth, int newHeight)
{
    title = newTitle;
    width = newWidth;
    height = newHeight;
}

SDLWindow::~SDLWindow()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
    LOG_DEBUG("SDL Window Destroyed.");
}

bool SDLWindow::onInit()
{
    // Initialize video and audio subsystem
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        LOG_ERROR("SDL Init Failed: {}", SDL_GetError());
        return false;
    }

#ifdef RENDERER_SDL
    window = SDL_CreateWindow(title.c_str(), width, height, 0);
#elif defined(RENDERER_OPENGL)
    window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
#endif

    if (!window)
    {
        LOG_ERROR("Failed to create Window: {}", SDL_GetError());
        SDL_Quit();
        return false;
    }

    LOG_DEBUG("SDL Window Initialized.");
    return true;
}

int SDLWindow::getWidth() const
{
    return width;
}

int SDLWindow::getHeight() const
{
    return height;
}

std::string SDLWindow::getTitle() const
{
    return title;
}

SDL_Window *SDLWindow::getWindowHandle() const
{
    return window;
}

void SDLWindow::quitGame()
{
    SDL_Event quit_event = {.type = SDL_EVENT_QUIT};
    SDL_PushEvent(&quit_event);
}
