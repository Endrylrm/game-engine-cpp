#pragma once
#include <string>

class Window
{
public:
    virtual ~Window() = default;
    virtual bool on_init() = 0;
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;
    virtual std::string get_title() const = 0;
    virtual void quit_game() = 0;
};