#include "engine/ecs/world/World.hpp"

#include <engine/core/log/Log.hpp>
#include <engine/ecs/handle/Entity.hpp>
#include <engine/ecs/systems/LifetimeSystem.hpp>
#include <engine/ecs/systems/MovementSystem.hpp>
#include <engine/ecs/systems/RenderSystem.hpp>

void World::init()
{
    systemManager.addSystem<LifetimeSystem>(SystemStage::Update);
    systemManager.addSystem<MovementSystem>(SystemStage::Update);
    systemManager.addSystem<RenderSystem>(SystemStage::Render);
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
    registry.processDestroyQueue();
    eventBus.removeDeletedEvents();
}

void World::unload()
{
    systemManager.unload();
}

Entity World::createEntity()
{
    EntityId id = registry.createEntity();
    Entity entity = {id, this};
    LOG_DEBUG("Entity Handle created from entity: '{}', generation: {}.", id.id, id.generation);
    return entity;
}

Entity World::getEntity(EntityId id)
{
    LOG_DEBUG("Entity Handle created from entity: '{}', generation: {}.", id.id, id.generation);
    return Entity{id, this};
}

void World::destroyEntity(EntityId entity)
{
    registry.destroyEntity(entity);
}

void World::removeAllComponents(EntityId entity)
{
    registry.removeAllComponents(entity);
}

bool World::isValidEntity(EntityId entity) const
{
    return registry.isValidEntity(entity);
}
