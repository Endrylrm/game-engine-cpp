#pragma once

class Game
{
public:
    virtual ~Game() = default;
    virtual void onInit() {}
    virtual void onBeginFrame() {}
    virtual void onPhysics(float fixedDeltaTime) {}
    virtual void onPreUpdate() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onPostUpdate() {}
    virtual void onRender() {}
    virtual void processLifecycle() {}
    virtual void onEndFrame() {}
    virtual void onShutdown() {}
};
