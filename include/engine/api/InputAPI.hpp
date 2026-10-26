#pragma once
#include "engine/api/ManagerAPI.hpp"
#include "engine/core/math/Vector2D.hpp"
#include "engine/input/InputManager.hpp"
#include "engine/input/KeyInput.hpp"
#include "engine/input/MouseInput.hpp"

class InputAPI : public ManagerAPI<InputManager>
{
public:
    static bool is_key_down(KeyInput key)
    {
        return get_manager().is_key_down(key);
    }

    static bool is_key_pressed(KeyInput key)
    {
        return get_manager().is_key_pressed(key);
    }

    static bool is_key_released(KeyInput key)
    {
        return get_manager().is_key_released(key);
    }

    static bool is_mouse_button_down(MouseInput key)
    {
        return get_manager().is_mouse_button_down(key);
    }

    static bool is_mouse_button_pressed(MouseInput key)
    {
        return get_manager().is_mouse_button_pressed(key);
    }

    static bool is_mouse_button_released(MouseInput key)
    {
        return get_manager().is_mouse_button_released(key);
    }

    static float get_mouse_x()
    {
        return get_manager().get_mouse_x();
    }

    static float get_mouse_y()
    {
        return get_manager().get_mouse_y();
    }

    static Vector2D get_mouse()
    {
        return get_manager().get_mouse();
    }

    static float get_mouse_delta_x()
    {
        return get_manager().get_mouse_delta_x();
    }

    static float get_mouse_delta_y()
    {
        return get_manager().get_mouse_delta_y();
    }

    static Vector2D get_mouse_delta()
    {
        return get_manager().get_mouse_delta();
    }

    static float get_mouse_scroll_x()
    {
        return get_manager().get_mouse_scroll_x();
    }

    static float get_mouse_scroll_y()
    {
        return get_manager().get_mouse_scroll_y();
    }

    static Vector2D get_mouse_scroll()
    {
        return get_manager().get_mouse_scroll();
    }
};
