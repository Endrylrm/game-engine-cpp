#pragma once
#include "engine/core/math/Vector2D.hpp"
#include "engine/core/input/KeyInput.hpp"
#include "engine/core/input/MouseInput.hpp"
#include "engine/core/input/MouseState.hpp"

class InputManager
{
public:
    virtual ~InputManager() = default;

    virtual void processEvent() = 0;
    virtual void beginFrame() = 0;

    virtual bool isKeyDown(KeyInput key) const = 0;
    virtual bool isKeyPressed(KeyInput key) const = 0;
    virtual bool isKeyReleased(KeyInput key) const = 0;

    virtual bool isMouseButtonDown(MouseInput key) const = 0;
    virtual bool isMouseButtonPressed(MouseInput key) const = 0;
    virtual bool isMouseButtonReleased(MouseInput key) const = 0;

    virtual float getMouseX() const = 0;
    virtual float getMouseY() const = 0;
    virtual Vector2D getMouse() const = 0;

    virtual float getMouseDeltaX() const = 0;
    virtual float getMouseDeltaY() const = 0;
    virtual Vector2D getMouseDelta() const = 0;

    virtual float getMouseScrollX() const = 0;
    virtual float getMouseScrollY() const = 0;
    virtual Vector2D getMouseScroll() const = 0;

protected:
    MouseState mouseState{};
};
