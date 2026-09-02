#pragma once
#include <string>

#include <SDL3/SDL.h>

#include <engine/core/window/Window.hpp>

class SDLWindow : public Window
{
public:
    SDLWindow(std::string newTitle, int newWidth, int newHeight);
    ~SDLWindow() override;
    bool onInit() override;
    int getWidth() const override;
    int getHeight() const override;
    std::string getTitle() const override;
    SDL_Window *getWindowHandle() const;
    void quitGame() override;

private:
    SDL_Window *window{};
    std::string title;
    int width;
    int height;
};
