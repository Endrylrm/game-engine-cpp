#pragma once
#include <string>

#include <SDL3/SDL.h>

#include "engine/window/Window.hpp"

class SDLWindow final : public Window
{
public:
    SDLWindow(std::string new_title, int new_width, int new_height);
    ~SDLWindow() override;
    bool on_init() override;
    int get_width() const override;
    int get_height() const override;
    std::string get_title() const override;
    SDL_Window *get_window_handle() const;
    void quit_game() override;

private:
    SDL_Window *window{};
    std::string title;
    int width;
    int height;
};
