#pragma once
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "engine/core/helpers/Flags.hpp"
#include "engine/core/string/StringHandle.hpp"
#include "engine/entities/EntityStateFlags.hpp"
#include "engine/entities/LifetimeState.hpp"
#include "engine/entities/components/Component.hpp"
#include "engine/entities/components/ComponentRegistry.hpp"
#include "engine/entities/components/Transform.hpp"

class Scene;
class EntityManager;

class Entity
{
    friend class Scene;
    friend class EntityManager;

public:
    Entity() {}
    ~Entity() = default;

    template <std::derived_from<Component> T, typename... Args>
    T *addComponent(Args &&...args)
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->owner = this;
        T *ptr = component.get();
        componentsMap[ComponentRegistry::getTypeId<T>()] = ptr;
        components.push_back(std::move(component));
        return ptr;
    }

    template <std::derived_from<Component> T>
    T *attachComponent(std::unique_ptr<T> component)
    {
        component->owner = this;
        T *ptr = component.get();
        componentsMap[ComponentRegistry::getTypeId<T>()] = ptr;
        components.push_back(std::move(component));
        return ptr;
    }

    template <typename T>
    T *getComponent()
    {
        auto iter = componentsMap.find(ComponentRegistry::getTypeId<T>());

        if (iter == componentsMap.end())
            return nullptr;

        return static_cast<T *>(iter->second);
    }

    template <typename T>
    bool hasComponent()
    {
        auto iter = componentsMap.find(ComponentRegistry::getTypeId<T>());

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

    Scene *getScene();

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

    StringHandle name;
    StringHandle tag;
    Transform transform;

private:
    Flags<EntityStateFlags> state{};
    LifetimeState lifetime{LifetimeState::PendingSpawn};
    Entity *parent{};
    std::vector<Entity *> children{};
    std::vector<std::unique_ptr<Component>> components{};
    std::unordered_map<ComponentId, Component *> componentsMap{};
    Scene *scene;
    size_t storageIndex = 0;
};

template <>
Transform *Entity::getComponent<Transform>();

template <>
bool Entity::hasComponent<Transform>();
