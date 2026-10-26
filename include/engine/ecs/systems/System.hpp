#pragma once
#include "engine/renderer/Renderer.hpp"

class World;

class System
{
public:
    virtual ~System() = default;

    virtual void on_init(World &world) {}
    virtual void on_physics(World &world, float fixed_delta_time) {}
    virtual void on_pre_update(World &world) {}
    virtual void on_update(World &world, float delta_time) {}
    virtual void on_post_update(World &world) {}
    virtual void on_render(World &world, Renderer &renderer) {}
    virtual void on_unload(World &world) {}
};
