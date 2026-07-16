#pragma once
#include <string>
#include "engine/api/ManagerAPI.hpp"
#include "engine/core/window/WindowManager.hpp"

class WindowAPI : public ManagerAPI<WindowManager>
{
public:
    static int getWidth()
    {
        return getManager().getWidth();
    }

    static int getHeight()
    {
        return getManager().getHeight();
    }

    static std::string getTitle()
    {
        return getManager().getTitle();
    }

    static void quit()
    {
        getManager().quitGame();
    }
};