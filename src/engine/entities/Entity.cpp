#include "engine/entities/Entity.hpp"

template <>
Transform2D *Entity::getComponent<Transform2D>()
{
	return &transform;
}

void Entity::onAwake()
{
	for (auto &component : components)
	{
		component->onAwake();
	}
}

void Entity::onActivate()
{
	for (auto &component : components)
	{
		component->onActivate();
	}
}

void Entity::onDeactivate()
{
	for (auto &component : components)
	{
		component->onDeactivate();
	}
}

void Entity::onStart()
{
	for (auto &component : components)
	{
		component->onStart();
	}
}

void Entity::onPhysics(float fixedDeltaTime)
{
	for (auto &component : components)
	{
		component->onPhysics(fixedDeltaTime);
	}
}

void Entity::onPreUpdate()
{
	for (auto &component : components)
	{
		component->onPreUpdate();
	}
}

void Entity::onUpdate(float deltaTime)
{
	for (auto &component : components)
	{
		component->onUpdate(deltaTime);
	}
}

void Entity::onPostUpdate()
{
	for (auto &component : components)
	{
		component->onPostUpdate();
	}
}

void Entity::onRender(Renderer &renderer)
{
	if (!isVisible())
		return;

	for (auto &component : components)
	{
		component->onRender(renderer);
	}
}

void Entity::onCollisionEnter(Entity &other)
{
	for (auto &component : components)
	{
		component->onCollisionEnter(other);
	}
}

void Entity::onCollisionStay(Entity &other)
{
	for (auto &component : components)
	{
		component->onCollisionStay(other);
	}
}

void Entity::onCollisionExit(Entity &other)
{
	for (auto &component : components)
	{
		component->onCollisionExit(other);
	}
}

void Entity::onDestruction()
{
	for (auto &component : components)
	{
		component->onDestruction();
	}
}

bool Entity::isPendingSpawn() const
{
	return state.has(EntityState::PendingSpawn);
}

void Entity::markSpawned()
{
	state.replace(EntityState::PendingSpawn, EntityState::PendingAwake);
}

bool Entity::isPendingAwake() const
{
	return state.has(EntityState::PendingAwake);
}

void Entity::markToStart()
{
	state.assign(EntityState::PendingStart);
}

bool Entity::isPendingStart() const
{
	return state.has(EntityState::PendingStart);
}

void Entity::markStarted()
{
	state.remove(EntityState::PendingStart);
}

bool Entity::isActive() const
{
	return state.has(EntityState::Active);
}

bool Entity::isDeactivated() const
{
	return state.has(EntityState::Deactivated);
}

void Entity::markActive()
{
	state.set(EntityState::Active, true);
}

void Entity::setActive(bool value)
{
	if (value && isActive())
		return;

	if (!value && isDeactivated())
		return;

	state.replace(
		value ? EntityState::Deactivated : EntityState::Active,
		value ? EntityState::Active : EntityState::Deactivated);

	if (value)
	{
		// in case the entity get's deactivated before the scene
		// this let's the entity awake normally
		if (isPendingAwake())
		{
			markToStart();
			onAwake();
		}

		onActivate();

		// in case the entity get's deactivated before the scene
		// this let's the entity starts normally
		if (isPendingStart())
		{
			markStarted();
			onStart();
			setVisible(true);
		}
	}
	else
	{
		onDeactivate();
	}
}

bool Entity::isVisible() const
{
	return state.has(EntityState::Visible);
}

void Entity::setVisible(bool value)
{
	state.set(EntityState::Visible, value);
}

bool Entity::isPendingDestruction() const
{
	return state.has(EntityState::PendingDestruction);
}

void Entity::markForDestruction()
{
	state.assign(EntityState::PendingDestruction);
}
