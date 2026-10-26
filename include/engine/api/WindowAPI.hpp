#pragma once
#include <string>

#include "engine/api/ManagerAPI.hpp"
#include "engine/window/Window.hpp"

class WindowAPI : public ManagerAPI<Window>
{
public:
    static int get_width()
    {
        return get_manager().get_width();
    }

    static int get_height()
    {
        return get_manager().get_height();
    }

    static std::string get_title()
    {
        return get_manager().get_title();
    }

    static void quit()
    {
        get_manager().quit_game();
    }
};
