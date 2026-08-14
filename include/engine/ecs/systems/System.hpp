#pragma once
#include <engine/core/graphics/Renderer.hpp>

class World;

class System
{
public:
    virtual ~System() = default;

    virtual void onInit(World &world) {}
    virtual void onPhysics(World &world, float fixedDeltaTime) {}
    virtual void onPreUpdate(World &world) {}
    virtual void onUpdate(World &world, float deltaTime) {}
    virtual void onPostUpdate(World &world) {}
    virtual void onRender(World &world, Renderer &renderer) {}
    virtual void onUnload(World &world) {}
};
