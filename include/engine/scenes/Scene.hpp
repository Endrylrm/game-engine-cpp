#pragma once
#include <functional>
#include <memory>

#include <engine/core/events/Connections.hpp>
#include <engine/core/events/EventBus.hpp>
#include <engine/core/graphics/Renderer.hpp>
#include <engine/core/helpers/Flags.hpp>
#include <engine/core/string/StringHandle.hpp>
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/registry/entities/EntityId.hpp>
#include <engine/ecs/registry/managers/SystemManager.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/systems/LifetimeSystem.hpp>
#include <engine/ecs/systems/MovementSystem.hpp>
#include <engine/ecs/systems/RenderSystem.hpp>
#include <engine/ecs/systems/System.hpp>

class Entity;

class Scene
{
public:
    Scene()
    {
        systemManager.addSystem<LifetimeSystem>(SystemStage::Update, registry);
        systemManager.addSystem<MovementSystem>(SystemStage::Update, registry);
        systemManager.addSystem<RenderSystem>(SystemStage::Render, registry);
    }
    ~Scene() = default;

    void init();
    void physics(float fixedDeltaTime);
    void preUpdate();
    void update(float deltaTime);
    void postUpdate();
    void render(Renderer &renderer);
    void processLifecycle();
    void unload();

    Entity createEntity();
    void queueDestroyEntity(EntityId entity);

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

    template <std::derived_from<System> T, typename... Args>
    T &addSystem(Flags<SystemStage> stages, Args &&...args)
    {
        return systemManager.addSystem<T>(stages, std::forward<Args>(args)...);
    }

    template <typename T>
    T *getSystem()
    {
        return systemManager.getSystem<T>();
    }

    Registry &getRegistry()
    {
        return registry;
    }

    StringHandle name;

private:
    Registry registry{};
    EventBus eventBus{};
    SystemManager systemManager{};
};
