#pragma once
#include "engine/ecs/handle/Entity.hpp"

class Script
{
public:
    virtual ~Script() = default;

    virtual void on_awake() {}
    virtual void on_activate() {}
    virtual void on_deactivate() {}
    virtual void on_start() {}
    virtual void on_physics(float fixedDeltaTime) {}
    virtual void on_pre_update() {}
    virtual void on_update(float deltaTime) {}
    virtual void on_post_update() {}
    virtual void on_collision_enter(Entity other) {}
    virtual void on_collision_stay(Entity other) {}
    virtual void on_collision_exit(Entity other) {}
    virtual void on_trigger_enter(Entity other) {}
    virtual void on_trigger_stay(Entity other) {}
    virtual void on_trigger_exit(Entity other) {}
    virtual void on_destruction() {}

    Entity owner;
};