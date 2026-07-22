#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/ComponentRegistry.hpp"
#include "engine/entities/components/Transform2D.hpp"
#include "engine/entities/EntityStateFlags.hpp"
#include "engine/entities/LifetimeState.hpp"
#include "engine/core/helpers/Flags.hpp"

class Entity
{
public:
	Entity() {}
	~Entity() = default;

	template <std::derived_from<Component> T, typename... Args>
	T *addComponent(Args &&...args)
	{
		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		component->owner = this;
		T *ptr = component.get();
		componentsMap[ComponentRegistry::GetId<T>()] = ptr;
		components.push_back(std::move(component));
		return ptr;
	}

	template <std::derived_from<Component> T>
	T *attachComponent(std::unique_ptr<T> component)
	{
		component->owner = this;
		T *ptr = component.get();
		componentsMap[ComponentRegistry::GetId<T>()] = ptr;
		components.push_back(std::move(component));
		return ptr;
	}

	template <typename T>
	T *getComponent()
	{
		auto iter = componentsMap.find(ComponentRegistry::GetId<T>());

		if (iter == componentsMap.end())
			return nullptr;

		return static_cast<T *>(iter->second);
	}

	template <typename T>
	bool hasComponent()
	{
		auto iter = componentsMap.find(ComponentRegistry::GetId<T>());

		if (iter == componentsMap.end())
			return false;

		return true;
	}

	void onAwake();
	void onActivate();
	void onDeactivate();
	void onStart();
	void onPhysics(float fixedDeltaTime);
	void onPreUpdate();
	void onUpdate(float deltaTime);
	void onPostUpdate();
	void onCollisionEnter(Entity &other);
	void onCollisionStay(Entity &other);
	void onCollisionExit(Entity &other);
	void onDestruction();

	Entity *getParent() const;
	void setParent(Entity *newParent);
	void addChild(Entity *child);
	void removeChild(Entity *child);
	bool isAncestorOf(Entity *entity) const;
	std::vector<Entity *> &getChildren();

	bool isPendingSpawn() const;
	void markSpawned();

	bool isPendingAwake() const;
	void markToStart();

	bool isPendingStart() const;
	void markStarted();

	bool isActive() const;
	bool isActiveInHierarchy() const;
	bool isDeactivated() const;
	void markActive();
	void setActive(bool value);

	bool isVisible() const;
	bool isVisibleInHierarchy() const;
	void setVisible(bool value);

	bool isPendingDestruction() const;
	void markForDestruction();

	std::string tag;
	Transform2D transform;

private:
	Flags<EntityStateFlags> state{};
	LifetimeState lifetime{LifetimeState::PendingSpawn};
	Entity *parent{};
	std::vector<Entity *> children;
	std::vector<std::unique_ptr<Component>> components;
	std::unordered_map<ComponentId, Component *> componentsMap;
};

template <>
Transform2D *Entity::getComponent<Transform2D>();

template <>
bool Entity::hasComponent<Transform2D>();
