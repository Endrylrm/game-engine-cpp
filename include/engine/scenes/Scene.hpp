#pragma once
#include <functional>
#include <memory>

#include <engine/core/events/Connections.hpp>
#include <engine/core/events/EventBus.hpp>
#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/string/StringHandle.hpp>
#include <engine/entities/Entity.hpp>
#include <engine/entities/EntityManager.hpp>
#include <engine/systems/RenderSystem.hpp>

class Scene
{
public:
    ~Scene() = default;

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

    StringHandle name;

private:
    EntityManager entityManager{};
    RenderSystem renderSystem{};
    EventBus eventBus{};
};
