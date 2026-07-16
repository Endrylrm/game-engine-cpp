#pragma once
#include <SDL3/SDL.h>
#include <unordered_set>
#include "engine/core/input/InputManager.hpp"
#include "engine/core/input/KeyInput.hpp"
#include "engine/core/input/MouseInput.hpp"
#include "engine/core/input/MouseState.hpp"
#include "engine/core/math/Vector2D.hpp"

class SDLInputManager : public InputManager
{
public:
    SDLInputManager(bool *isRunning);
    ~SDLInputManager() override = default;

    void processEvent() override;
    void beginFrame() override;
    bool isKeyDown(KeyInput key) const override;
    bool isKeyPressed(KeyInput key) const override;
    bool isKeyReleased(KeyInput key) const override;

    bool isMouseButtonDown(MouseInput key) const override;
    bool isMouseButtonPressed(MouseInput key) const override;
    bool isMouseButtonReleased(MouseInput key) const override;

    float getMouseX() const override;
    float getMouseY() const override;
    Vector2D getMouse() const override;

    float getMouseDeltaX() const override;
    float getMouseDeltaY() const override;
    Vector2D getMouseDelta() const override;

    float getMouseScrollX() const override;
    float getMouseScrollY() const override;
    Vector2D getMouseScroll() const override;

private:
    KeyInput translateKey(SDL_Keycode key);
    MouseInput translateMouseButton(Uint8 key);

    std::unordered_set<KeyInput> keysDown;
    std::unordered_set<KeyInput> keysPressed;
    std::unordered_set<KeyInput> keysReleased;

    std::unordered_set<MouseInput> mouseDown;
    std::unordered_set<MouseInput> mousePressed;
    std::unordered_set<MouseInput> mouseReleased;

    bool *running = nullptr;
};
