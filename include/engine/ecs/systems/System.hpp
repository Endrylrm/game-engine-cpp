#pragma once
#include <engine/core/graphics/Renderer.hpp>

class System
{
public:
    virtual ~System() = default;

    virtual void onInit() {}
    virtual void onPhysics(float fixedDeltaTime) {}
    virtual void onPreUpdate() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onPostUpdate() {}
    virtual void onRender(Renderer &renderer) {}
    virtual void onUnload() {}
};