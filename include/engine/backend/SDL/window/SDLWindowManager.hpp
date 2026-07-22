#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <memory>
#include "engine/core/window/WindowManager.hpp"

class SDLWindowManager : public WindowManager
{
public:
    SDLWindowManager(std::string newTitle, int newWidth, int newHeight);
    ~SDLWindowManager() override;
    bool onInit() override;
    int getWidth() const override;
    int getHeight() const override;
    std::string getTitle() const override;
    void *getWindowHandle() const override;
    void quitGame() override;

private:
    SDL_Window *window{};
    std::string title;
    int width;
    int height;
};