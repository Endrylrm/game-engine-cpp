#pragma once

class Game
{
public:
    virtual ~Game() = default;
    virtual void on_init() {}
    virtual void on_begin_frame() {}
    virtual void on_physics(float fixed_delta_time) {}
    virtual void on_pre_update() {}
    virtual void on_update(float delta_time) {}
    virtual void on_post_update() {}
    virtual void on_render() {}
    virtual void process_lifecycle() {}
    virtual void on_end_frame() {}
    virtual void on_shutdown() {}
};
