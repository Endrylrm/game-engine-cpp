#pragma once
#include "engine/core/math/Vector2D.hpp"

#include "KeyInput.hpp"
#include "MouseInput.hpp"
#include "MouseState.hpp"

class InputManager
{
public:
    virtual ~InputManager() = default;

    virtual void process_event() = 0;
    virtual void begin_frame() = 0;

    virtual bool is_key_down(KeyInput key) const = 0;
    virtual bool is_key_pressed(KeyInput key) const = 0;
    virtual bool is_key_released(KeyInput key) const = 0;

    virtual bool is_mouse_button_down(MouseInput key) const = 0;
    virtual bool is_mouse_button_pressed(MouseInput key) const = 0;
    virtual bool is_mouse_button_released(MouseInput key) const = 0;

    virtual float get_mouse_x() const = 0;
    virtual float get_mouse_y() const = 0;
    virtual Vector2D get_mouse() const = 0;

    virtual float get_mouse_delta_x() const = 0;
    virtual float get_mouse_delta_y() const = 0;
    virtual Vector2D get_mouse_delta() const = 0;

    virtual float get_mouse_scroll_x() const = 0;
    virtual float get_mouse_scroll_y() const = 0;
    virtual Vector2D get_mouse_scroll() const = 0;

protected:
    MouseState mouse_state{};
};
