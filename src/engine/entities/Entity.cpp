#include "engine/entities/Entity.hpp"

template <>
Transform2D *Entity::getComponent<Transform2D>()
{
	return &transform;
}

template <>
bool Entity::hasComponent<Transform2D>()
{
	return true;
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

Entity *Entity::getParent() const
{
	return parent;
}

void Entity::setParent(Entity *newParent)
{
	if (parent == newParent)
		return;

	if (parent)
		parent->removeChild(this);

	parent = newParent;
}

void Entity::addChild(Entity *child)
{
	if (child->parent == this)
		return;

	if (child->isAncestorOf(this))
		return;

	if (child->parent)
		child->parent->removeChild(child);

	children.push_back(child);
	child->parent = this;
}

void Entity::removeChild(Entity *child)
{
	auto iter = std::find(children.begin(), children.end(), child);

	if (iter != children.end())
	{
		children.erase(iter);
		child->parent = nullptr;
	}
}

bool Entity::isAncestorOf(Entity *entity) const
{
	while (entity)
	{
		if (entity == this)
			return true;
		entity = entity->parent;
	}
	return false;
}

std::vector<Entity *> &Entity::getChildren()
{
	return children;
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

bool Entity::isActiveInHierarchy() const
{
	return isActive() && (!parent || parent->isActiveInHierarchy());
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

bool Entity::isVisibleInHierarchy() const
{
	return isVisible() && (!parent || parent->isVisibleInHierarchy());
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
	if (state == EntityState::PendingDestruction)
		return;

	state.assign(EntityState::PendingDestruction);

	for (auto *child : children)
		child->markForDestruction();
}
