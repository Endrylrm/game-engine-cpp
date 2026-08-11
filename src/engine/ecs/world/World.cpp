#include "engine/ecs/world/World.hpp"

#include <engine/core/log/Log.hpp>
#include <engine/ecs/handle/Entity.hpp>

void World::init()
{
    systemManager.init();
}

void World::events()
{
    eventBus.processEvents();
}

void World::physics(float fixedDeltaTime)
{
    systemManager.physics(fixedDeltaTime);
}

void World::preUpdate()
{
    systemManager.preUpdate();
}

void World::update(float deltaTime)
{
    systemManager.update(deltaTime);
}

void World::postUpdate()
{
    systemManager.postUpdate();
}

void World::render(Renderer &renderer)
{
    systemManager.render(renderer);
}

void World::processLifecycle()
{
    eventBus.removeDeletedEvents();
}

void World::unload()
{
    systemManager.unload();
}

Entity World::createEntity()
{
    EntityId id = registry.createEntity();
    Entity entity = {id, nullptr};
    LOG_DEBUG("Entity id: '{}', generation: {} created!", id.id, id.generation);
    return entity;
}

void World::queueDestroyEntity(EntityId entity)
{
    registry.destroyEntity(entity);
}

void World::removeAllComponents(EntityId entity)
{
    registry.removeAllComponents(entity);
}

EventBus &World::getEventBus()
{
    return eventBus;
}
