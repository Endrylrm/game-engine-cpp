#pragma once
#include <functional>
#include <memory>
#include "engine/core/graphics/Renderer.hpp"
#include "engine/entities/EntityManager.hpp"
#include "engine/entities/Entity.hpp"
#include "engine/systems/RenderSystem.hpp"
#include "engine/core/events/EventBus.hpp"
#include "engine/core/events/Connections.hpp"

class Scene
{
public:
	virtual ~Scene() = default;

	void init()
	{
		renderSystem.setEventBus(&eventBus);
		entityManager.onInit();
		renderSystem.onInit();
		onInit();
	}

	void physics(float fixedDeltaTime)
	{
		entityManager.onPhysics(fixedDeltaTime);
		onPhysics(fixedDeltaTime);
	}

	void preUpdate()
	{
		eventBus.processEvents();
		entityManager.onPreUpdate();
		onPreUpdate();
	}

	void update(float deltaTime)
	{
		entityManager.onUpdate(deltaTime);
		onUpdate(deltaTime);
	}

	void postUpdate()
	{
		entityManager.onPostUpdate();
		onPostUpdate();
	}

	void render(Renderer &renderer)
	{
		renderSystem.onRender(renderer);
		onRender(renderer);
	}

	void processLifecycle()
	{
		eventBus.removeDeletedEvents();
		entityManager.removeDestroyedObjects();
		entityManager.processPendingSpawns();
		entityManager.processAwakeQueue();
		entityManager.processStartQueue();
	}

	void unload()
	{
		entityManager.clearEntities();
		renderSystem.onUnload();
		onUnload();
	}

	Entity *createEntity() 
	{
		Entity *ptr = entityManager.createEntity();
		ptr->scene = this;
		return ptr;
	}

	Entity *createEntity(std::unique_ptr<Entity> entityBlueprint) 
	{
		Entity *ptr = entityManager.createEntity(std::move(entityBlueprint));
		ptr->scene = this;
		return ptr;
	}

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
