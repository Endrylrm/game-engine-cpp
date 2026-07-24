#pragma once
#include "engine/core/events/Event.hpp"
#include "engine/entities/Entity.hpp"

template <typename T>
struct ComponentAddedEvent : public Event
{
    explicit ComponentAddedEvent(Entity *entity, T *component) : entity(entity), component(component) {}

    Entity *entity;
    T *component;
};

template <typename T>
struct ComponentRemovedEvent : public Event
{
    explicit ComponentRemovedEvent(Entity *entity, T *component) : entity(entity), component(component) {}

    Entity *entity;
    T *component;
};