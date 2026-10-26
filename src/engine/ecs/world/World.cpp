#include "engine/ecs/world/World.hpp"

#include "engine/core/log/Log.hpp"
#include "engine/ecs/handle/Entity.hpp"
#include "engine/ecs/systems/LifetimeSystem.hpp"
#include "engine/ecs/systems/MovementSystem.hpp"
#include "engine/ecs/systems/RenderSystem.hpp"

void World::init()
{
    system_manager.add_system<LifetimeSystem>(SystemStage::Update);
    system_manager.add_system<MovementSystem>(SystemStage::Update);
    system_manager.add_system<RenderSystem>(SystemStage::Render);
    system_manager.init();
}

void World::events()
{
    event_bus.process_events();
}

void World::physics(float fixed_delta_time)
{
    system_manager.physics(fixed_delta_time);
}

void World::pre_update()
{
    system_manager.pre_update();
}

void World::update(float delta_time)
{
    system_manager.update(delta_time);
}

void World::post_update()
{
    system_manager.post_update();
}

void World::render(Renderer &renderer)
{
    system_manager.render(renderer);
}

void World::process_lifecycle()
{
    registry.process_destroy_queue();
    event_bus.remove_deleted_events();
}

void World::unload()
{
    system_manager.unload();
}

Entity World::create_entity()
{
    EntityId id = registry.create_entity();
    Entity entity = {id, this};
    LOG_DEBUG("Entity Handle created from entity: '{}', generation: {}.", id.index, id.generation);
    return entity;
}

Entity World::get_entity(EntityId id)
{
    LOG_DEBUG("Entity Handle created from entity: '{}', generation: {}.", id.index, id.generation);
    return Entity{id, this};
}

void World::destroy_entity(EntityId entity)
{
    registry.destroy_entity(entity);
}

void World::remove_all_components(EntityId entity)
{
    registry.remove_all_components(entity);
}

bool World::is_valid_entity(EntityId entity) const
{
    return registry.is_valid_entity(entity);
}
