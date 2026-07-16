#include "engine/backend/SDL/window/SDLWindowManager.hpp"

SDLWindowManager::SDLWindowManager(std::string newTitle, int newWidth, int newHeight)
{
    title = newTitle;
    width = newWidth;
    height = newHeight;
}

bool SDLWindowManager::onInit()
{
    // Initialize video and audio subsystem
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_Log("SDL Init Failed: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), width, height, 0);

    if (!window)
    {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

int SDLWindowManager::getWidth() const
{
    return width;
}

int SDLWindowManager::getHeight() const
{
    return height;
}

std::string SDLWindowManager::getTitle() const
{
    return title;
}

void *SDLWindowManager::getWindowHandle() const
{
    return window;
}

void SDLWindowManager::quitGame()
{
    SDL_Event quit_event = {.type = SDL_EVENT_QUIT};
    SDL_PushEvent(&quit_event);
}

SDLWindowManager::~SDLWindowManager()
{
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}
