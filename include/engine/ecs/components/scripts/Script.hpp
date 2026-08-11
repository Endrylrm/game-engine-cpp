#pragma once
#include "engine/ecs/handle/Entity.hpp"

class Script
{
public:
    virtual ~Script() = default;

    virtual void onAwake() {}
    virtual void onActivate() {}
    virtual void onDeactivate() {}
    virtual void onStart() {}
    virtual void onPhysics(float fixedDeltaTime) {}
    virtual void onPreUpdate() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onPostUpdate() {}
    virtual void onCollisionEnter(Entity other) {}
    virtual void onCollisionStay(Entity other) {}
    virtual void onCollisionExit(Entity other) {}
    virtual void onTriggerEnter(Entity other) {}
    virtual void onTriggerStay(Entity other) {}
    virtual void onTriggerExit(Entity other) {}
    virtual void onDestruction() {}

    Entity owner;
};