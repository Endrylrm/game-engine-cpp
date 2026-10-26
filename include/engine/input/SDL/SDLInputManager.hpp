#pragma once
#include <unordered_set>

#include <SDL3/SDL.h>

#include "engine/core/math/Vector2D.hpp"
#include "engine/input/InputManager.hpp"
#include "engine/input/KeyInput.hpp"
#include "engine/input/MouseInput.hpp"
#include "engine/input/MouseState.hpp"

class SDLInputManager final : public InputManager
{
public:
    SDLInputManager(bool *is_running);
    ~SDLInputManager() override = default;

    void process_event() override;
    void begin_frame() override;
    bool is_key_down(KeyInput key) const override;
    bool is_key_pressed(KeyInput key) const override;
    bool is_key_released(KeyInput key) const override;

    bool is_mouse_button_down(MouseInput key) const override;
    bool is_mouse_button_pressed(MouseInput key) const override;
    bool is_mouse_button_released(MouseInput key) const override;

    float get_mouse_x() const override;
    float get_mouse_y() const override;
    Vector2D get_mouse() const override;

    float get_mouse_delta_x() const override;
    float get_mouse_delta_y() const override;
    Vector2D get_mouse_delta() const override;

    float get_mouse_scroll_x() const override;
    float get_mouse_scroll_y() const override;
    Vector2D get_mouse_scroll() const override;

private:
    KeyInput translate_key(SDL_Keycode key);
    MouseInput translate_mouse_button(Uint8 key);

    std::unordered_set<KeyInput> keys_down;
    std::unordered_set<KeyInput> keys_pressed;
    std::unordered_set<KeyInput> keys_released;

    std::unordered_set<MouseInput> mouse_down;
    std::unordered_set<MouseInput> mouse_pressed;
    std::unordered_set<MouseInput> mouse_released;

    bool *running{};
};
