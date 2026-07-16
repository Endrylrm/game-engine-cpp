#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/core/input/InputManager.hpp"
#include "engine/core/input/KeyInput.hpp"
#include "engine/core/input/MouseInput.hpp"
#include "engine/core/math/Vector2D.hpp"

class InputAPI : public ManagerAPI<InputManager>
{
public:
    static bool isKeyDown(KeyInput key)
    {
        return getManager().isKeyDown(key);
    }

    static bool isKeyPressed(KeyInput key)
    {
        return getManager().isKeyPressed(key);
    }

    static bool isKeyReleased(KeyInput key)
    {
        return getManager().isKeyReleased(key);
    }

    static bool isMouseButtonDown(MouseInput key)
    {
        return getManager().isMouseButtonDown(key);
    }

    static bool isMouseButtonPressed(MouseInput key)
    {
        return getManager().isMouseButtonPressed(key);
    }

    static bool isMouseButtonReleased(MouseInput key)
    {
        return getManager().isMouseButtonReleased(key);
    }

    static float getMouseX()
    {
        return getManager().getMouseX();
    }

    static float getMouseY()
    {
        return getManager().getMouseY();
    }

    static Vector2D getMouse()
    {
        return getManager().getMouse();
    }

    static float getMouseDeltaX()
    {
        return getManager().getMouseDeltaX();
    }

    static float getMouseDeltaY()
    {
        return getManager().getMouseDeltaY();
    }

    static Vector2D getMouseDelta()
    {
        return getManager().getMouseDelta();
    }

    static float getMouseScrollX()
    {
        return getManager().getMouseScrollX();
    }

    static float getMouseScrollY()
    {
        return getManager().getMouseScrollY();
    }

    static Vector2D getMouseScroll()
    {
        return getManager().getMouseScroll();
    }
};