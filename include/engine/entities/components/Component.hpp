#pragma once

// forward declaration
class Entity;

class Component
{
public:
    virtual ~Component() = default;
    virtual void onAwake() {}
    virtual void onActivate() {}
    virtual void onDeactivate() {}
    virtual void onStart() {}
    virtual void onPhysics(float fixedDeltaTime) {}
    virtual void onPreUpdate() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onPostUpdate() {}
    virtual void onCollisionEnter(Entity &other) {}
    virtual void onCollisionStay(Entity &other) {}
    virtual void onCollisionExit(Entity &other) {}
    virtual void onDestruction() {}

    Entity *owner = nullptr;
};
