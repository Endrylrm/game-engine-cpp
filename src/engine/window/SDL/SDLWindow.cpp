#include "engine/window/SDL/SDLWindow.hpp"

#include <SDL3/SDL_video.h>

#include "engine/core/log/Log.hpp"

SDLWindow::SDLWindow(std::string new_title, int new_width, int new_height)
{
    title = new_title;
    width = new_width;
    height = new_height;
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

bool SDLWindow::on_init()
{
    // Initialize video and audio subsystem
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        LOG_ERROR("SDL Init Failed: {}", SDL_GetError());
        return false;
    }

    SDL_WindowFlags flags = SDL_WINDOW_HIGH_PIXEL_DENSITY;

#ifdef RENDERER_OPENGL
    flags |= SDL_WINDOW_OPENGL;
#endif

    window = SDL_CreateWindow(title.c_str(), width, height, flags);

    if (!window)
    {
        LOG_ERROR("Failed to create Window: {}", SDL_GetError());
        SDL_Quit();
        return false;
    }

    LOG_DEBUG("SDL Window Initialized.");
    return true;
}

int SDLWindow::get_width() const
{
    return width;
}

int SDLWindow::get_height() const
{
    return height;
}

std::string SDLWindow::get_title() const
{
    return title;
}

SDL_Window *SDLWindow::get_window_handle() const
{
    return window;
}

void SDLWindow::quit_game()
{
    SDL_Event quit_event = {.type = SDL_EVENT_QUIT};
    SDL_PushEvent(&quit_event);
}
