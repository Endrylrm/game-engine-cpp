#pragma once
#include <functional>
#include <memory>

#include "engine/core/events/Connections.hpp"
#include "engine/core/events/EventBus.hpp"
#include "engine/core/graphics/Renderer.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/entities/EntityManager.hpp"
#include "engine/systems/RenderSystem.hpp"

class Scene
{
public:
    virtual ~Scene() = default;

    void init();
    void physics(float fixedDeltaTime);
    void preUpdate();
    void update(float deltaTime);
    void postUpdate();
    void render(Renderer &renderer);
    void processLifecycle();
    void unload();

    Entity *createEntity();
    Entity *createEntity(std::unique_ptr<Entity> entityBlueprint);
    void queueDestroyEntity(Entity *entity);

    template <typename EventType, typename Callback>
    EventConnection connectEvent(Callback &&callback)
    {
        return eventBus.connect<EventType>(std::forward<Callback>(callback));
    }

    template <typename EventType>
    void emitEvent(const EventType &event)
    {
        eventBus.emit<EventType>(event);
    }

    template <typename EventType>
    void dispatchEvent(const EventType &event)
    {
        eventBus.dispatch<EventType>(event);
    }

protected:
    virtual void onInit() {}
    virtual void onPhysics(float fixedDeltaTime) {}
    virtual void onPreUpdate() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onPostUpdate() {}
    virtual void onRender(Renderer &renderer) {}
    virtual void onUnload() {}

private:
    EntityManager entityManager{};
    RenderSystem renderSystem{};
    EventBus eventBus{};
};
