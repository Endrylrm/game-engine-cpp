#pragma once
#include <vector>
#include <memory>
#include "engine/entities/Entity.hpp"
#include "engine/core/graphics/Renderer.hpp"
#include "engine/entities/EntityManager.hpp"
#include "engine/systems/RenderSystem.hpp"

class Scene
{
public:
	virtual ~Scene() = default;

	Entity *createEntity()
	{
		Entity *ptr = entityManager.createEntity();
		return ptr;
	}

	Entity *createEntity(std::unique_ptr<Entity> entityBlueprint)
	{
		Entity *ptr = entityManager.createEntity(std::move(entityBlueprint));
		return ptr;
	}

	void init()
	{
		entityManager.onInit();
		onInit();
	}

	void physics(float fixedDeltaTime)
	{
		entityManager.onPhysics(fixedDeltaTime);
		onPhysics(fixedDeltaTime);
	}

	void preUpdate()
	{
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
		renderSystem.render(entityManager, renderer);
		onRender(renderer);
	}

	void processLifecycle()
	{
		entityManager.removeDestroyedObjects();
		entityManager.processPendingSpawns();
		entityManager.processAwakeQueue();
		entityManager.processStartQueue();
	}

	void unload()
	{
		entityManager.clearEntities();
		onUnload();
	}

	EntityManager &getEntityManager()
	{
		return entityManager;
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
	EntityManager entityManager;
	RenderSystem renderSystem;
};
