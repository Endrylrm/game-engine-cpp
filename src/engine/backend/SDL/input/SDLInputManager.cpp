#include <iostream>
#include "engine/backend/SDL/input/SDLInputManager.hpp"

SDLInputManager::SDLInputManager(bool *isRunning)
{
    running = isRunning;
}

void SDLInputManager::processEvent()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:
        {
            KeyInput key = translateKey(event.key.key);

            if (!keysDown.contains(key))
                keysPressed.insert(key);

            keysDown.insert(key);
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            KeyInput key = translateKey(event.key.key);

            keysDown.erase(key);
            keysReleased.insert(key);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            MouseInput btn = translateMouseButton(event.button.button);

            if (!mouseDown.contains(btn))
                mousePressed.insert(btn);

            mouseDown.insert(btn);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            MouseInput btn = translateMouseButton(event.button.button);

            mouseDown.erase(btn);
            mouseReleased.insert(btn);
            break;
        }
        case SDL_EVENT_MOUSE_MOTION:
        {
            mouseState.x = event.motion.x;
            mouseState.y = event.motion.y;

            mouseState.dx += event.motion.xrel;
            mouseState.dy += event.motion.yrel;

            break;
        }
        case SDL_EVENT_MOUSE_WHEEL:
        {
            mouseState.scrollX += event.wheel.x;
            mouseState.scrollY += event.wheel.y;

            break;
        }
        case SDL_EVENT_QUIT:
            *running = false;
            break;
        }
    }
}

void SDLInputManager::beginFrame()
{
    keysPressed.clear();
    keysReleased.clear();
    mousePressed.clear();
    mouseReleased.clear();

    mouseState.dx = 0;
    mouseState.dy = 0;

    mouseState.scrollX = 0;
    mouseState.scrollY = 0;
}

bool SDLInputManager::isKeyDown(KeyInput key) const
{
    return keysDown.contains(key);
}

bool SDLInputManager::isKeyPressed(KeyInput key) const
{
    return keysPressed.contains(key);
}

bool SDLInputManager::isKeyReleased(KeyInput key) const
{
    return keysReleased.contains(key);
}

bool SDLInputManager::isMouseButtonDown(MouseInput key) const
{
    return mouseDown.contains(key);
}

bool SDLInputManager::isMouseButtonPressed(MouseInput key) const
{
    return mousePressed.contains(key);
}

bool SDLInputManager::isMouseButtonReleased(MouseInput key) const
{
    return mouseReleased.contains(key);
}

float SDLInputManager::getMouseX() const
{
    return mouseState.x;
}

float SDLInputManager::getMouseY() const
{
    return mouseState.y;
}

Vector2D SDLInputManager::getMouse() const
{
    return Vector2D{mouseState.x, mouseState.y};
}

float SDLInputManager::getMouseDeltaX() const
{
    return mouseState.dx;
}

float SDLInputManager::getMouseDeltaY() const
{
    return mouseState.dy;
}

Vector2D SDLInputManager::getMouseDelta() const
{
    return Vector2D{mouseState.dx, mouseState.dy};
}

float SDLInputManager::getMouseScrollX() const
{
    return mouseState.scrollX;
}

float SDLInputManager::getMouseScrollY() const
{
    return mouseState.scrollY;
}

Vector2D SDLInputManager::getMouseScroll() const
{
    return Vector2D{mouseState.scrollX, mouseState.scrollY};
}

KeyInput SDLInputManager::translateKey(SDL_Keycode key)
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

MouseInput SDLInputManager::translateMouseButton(Uint8 key)
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