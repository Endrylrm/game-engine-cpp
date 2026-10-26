#include "engine/input/SDL/SDLInputManager.hpp"

#include <iostream>

SDLInputManager::SDLInputManager(bool *is_running)
{
    running = is_running;
}

void SDLInputManager::process_event()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:
        {
            KeyInput key = translate_key(event.key.key);

            if (!keys_down.contains(key))
                keys_pressed.insert(key);

            keys_down.insert(key);
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            KeyInput key = translate_key(event.key.key);

            keys_down.erase(key);
            keys_released.insert(key);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            MouseInput btn = translate_mouse_button(event.button.button);

            if (!mouse_down.contains(btn))
                mouse_pressed.insert(btn);

            mouse_down.insert(btn);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            MouseInput btn = translate_mouse_button(event.button.button);

            mouse_down.erase(btn);
            mouse_released.insert(btn);
            break;
        }
        case SDL_EVENT_MOUSE_MOTION:
        {
            mouse_state.x = event.motion.x;
            mouse_state.y = event.motion.y;

            mouse_state.dx += event.motion.xrel;
            mouse_state.dy += event.motion.yrel;

            break;
        }
        case SDL_EVENT_MOUSE_WHEEL:
        {
            mouse_state.scroll_x += event.wheel.x;
            mouse_state.scroll_y += event.wheel.y;

            break;
        }
        case SDL_EVENT_QUIT:
            *running = false;
            break;
        }
    }
}

void SDLInputManager::begin_frame()
{
    keys_pressed.clear();
    keys_released.clear();
    mouse_pressed.clear();
    mouse_released.clear();

    mouse_state.dx = 0;
    mouse_state.dy = 0;

    mouse_state.scroll_x = 0;
    mouse_state.scroll_y = 0;
}

bool SDLInputManager::is_key_down(KeyInput key) const
{
    return keys_down.contains(key);
}

bool SDLInputManager::is_key_pressed(KeyInput key) const
{
    return keys_pressed.contains(key);
}

bool SDLInputManager::is_key_released(KeyInput key) const
{
    return keys_released.contains(key);
}

bool SDLInputManager::is_mouse_button_down(MouseInput key) const
{
    return mouse_down.contains(key);
}

bool SDLInputManager::is_mouse_button_pressed(MouseInput key) const
{
    return mouse_pressed.contains(key);
}

bool SDLInputManager::is_mouse_button_released(MouseInput key) const
{
    return mouse_released.contains(key);
}

float SDLInputManager::get_mouse_x() const
{
    return mouse_state.x;
}

float SDLInputManager::get_mouse_y() const
{
    return mouse_state.y;
}

Vector2D SDLInputManager::get_mouse() const
{
    return Vector2D{mouse_state.x, mouse_state.y};
}

float SDLInputManager::get_mouse_delta_x() const
{
    return mouse_state.dx;
}

float SDLInputManager::get_mouse_delta_y() const
{
    return mouse_state.dy;
}

Vector2D SDLInputManager::get_mouse_delta() const
{
    return Vector2D{mouse_state.dx, mouse_state.dy};
}

float SDLInputManager::get_mouse_scroll_x() const
{
    return mouse_state.scroll_x;
}

float SDLInputManager::get_mouse_scroll_y() const
{
    return mouse_state.scroll_y;
}

Vector2D SDLInputManager::get_mouse_scroll() const
{
    return Vector2D{mouse_state.scroll_x, mouse_state.scroll_y};
}

KeyInput SDLInputManager::translate_key(SDL_Keycode key)
{
    switch (key)
    {
    // Alphanumerics
    case SDLK_A:
        return KeyInput::A;
    case SDLK_B:
        return KeyInput::B;
    case SDLK_C:
        return KeyInput::C;
    case SDLK_D:
        return KeyInput::D;
    case SDLK_E:
        return KeyInput::E;
    case SDLK_F:
        return KeyInput::F;
    case SDLK_G:
        return KeyInput::G;
    case SDLK_H:
        return KeyInput::H;
    case SDLK_I:
        return KeyInput::I;
    case SDLK_J:
        return KeyInput::J;
    case SDLK_K:
        return KeyInput::K;
    case SDLK_L:
        return KeyInput::L;
    case SDLK_M:
        return KeyInput::M;
    case SDLK_N:
        return KeyInput::N;
    case SDLK_O:
        return KeyInput::O;
    case SDLK_P:
        return KeyInput::P;
    case SDLK_Q:
        return KeyInput::Q;
    case SDLK_R:
        return KeyInput::R;
    case SDLK_S:
        return KeyInput::S;
    case SDLK_T:
        return KeyInput::T;
    case SDLK_U:
        return KeyInput::U;
    case SDLK_V:
        return KeyInput::V;
    case SDLK_W:
        return KeyInput::W;
    case SDLK_X:
        return KeyInput::X;
    case SDLK_Y:
        return KeyInput::Y;
    case SDLK_Z:
        return KeyInput::Z;

    case SDLK_0:
        return KeyInput::Num0;
    case SDLK_1:
        return KeyInput::Num1;
    case SDLK_2:
        return KeyInput::Num2;
    case SDLK_3:
        return KeyInput::Num3;
    case SDLK_4:
        return KeyInput::Num4;
    case SDLK_5:
        return KeyInput::Num5;
    case SDLK_6:
        return KeyInput::Num6;
    case SDLK_7:
        return KeyInput::Num7;
    case SDLK_8:
        return KeyInput::Num8;
    case SDLK_9:
        return KeyInput::Num9;

    // Controls and Modifiers
    case SDLK_ESCAPE:
        return KeyInput::Escape;
    case SDLK_SPACE:
        return KeyInput::Space;
    case SDLK_RETURN:
        return KeyInput::Enter;
    case SDLK_BACKSPACE:
        return KeyInput::Backspace;
    case SDLK_TAB:
        return KeyInput::Tab;
    case SDLK_LSHIFT:
        return KeyInput::LeftShift;
    case SDLK_RSHIFT:
        return KeyInput::RightShift;
    case SDLK_LCTRL:
        return KeyInput::LeftControl;
    case SDLK_RCTRL:
        return KeyInput::RightControl;
    case SDLK_LALT:
        return KeyInput::LeftAlt;
    case SDLK_RALT:
        return KeyInput::RightAlt;

    // Navigation
    case SDLK_UP:
        return KeyInput::Up;
    case SDLK_DOWN:
        return KeyInput::Down;
    case SDLK_LEFT:
        return KeyInput::Left;
    case SDLK_RIGHT:
        return KeyInput::Right;

    // Functions Keys
    case SDLK_F1:
        return KeyInput::F1;
    case SDLK_F2:
        return KeyInput::F2;
    case SDLK_F3:
        return KeyInput::F3;
    case SDLK_F4:
        return KeyInput::F4;
    case SDLK_F5:
        return KeyInput::F5;
    case SDLK_F6:
        return KeyInput::F6;
    case SDLK_F7:
        return KeyInput::F7;
    case SDLK_F8:
        return KeyInput::F8;
    case SDLK_F9:
        return KeyInput::F9;
    case SDLK_F10:
        return KeyInput::F10;
    case SDLK_F11:
        return KeyInput::F11;
    case SDLK_F12:
        return KeyInput::F12;

    default:
        return KeyInput::Unknown;
    }
}

MouseInput SDLInputManager::translate_mouse_button(Uint8 key)
{
    switch (key)
    {
    case SDL_BUTTON_LEFT:
        return MouseInput::Left;
    case SDL_BUTTON_MIDDLE:
        return MouseInput::Middle;
    case SDL_BUTTON_RIGHT:
        return MouseInput::Right;
    case SDL_BUTTON_X1:
        return MouseInput::Button4;
    case SDL_BUTTON_X2:
        return MouseInput::Button5;
    default:
        return MouseInput::None;
    }
}
