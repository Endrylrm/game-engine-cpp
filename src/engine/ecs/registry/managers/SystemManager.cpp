#include "engine/ecs/registry/managers/SystemManager.hpp"

#include "engine/ecs/world/World.hpp"

void SystemManager::init()
{
    for (auto &entry : systems)
        entry.system->on_init(world);
}

void SystemManager::physics(float fixed_delta_time)
{
    for (auto *system : physics_systems)
        system->on_physics(world, fixed_delta_time);
}

void SystemManager::pre_update()
{
    for (auto *system : pre_update_systems)
        system->on_pre_update(world);
}

void SystemManager::update(float delta_time)
{
    for (auto *system : update_systems)
        system->on_update(world, delta_time);
}

void SystemManager::post_update()
{
    for (auto *system : post_update_systems)
        system->on_post_update(world);
}

void SystemManager::render(Renderer &renderer)
{
    for (auto *system : render_systems)
        system->on_render(world, renderer);
}

void SystemManager::unload()
{
    for (auto &entry : systems)
        entry.system->on_unload(world);

    systems.clear();
    physics_systems.clear();
    pre_update_systems.clear();
    update_systems.clear();
    post_update_systems.clear();
    render_systems.clear();
}

void SystemManager::register_system(System &system, Flags<SystemStage> stages)
{
    if (stages.has(SystemStage::Physics))
        physics_systems.push_back(&system);

    if (stages.has(SystemStage::PreUpdate))
        pre_update_systems.push_back(&system);

    if (stages.has(SystemStage::Update))
        update_systems.push_back(&system);

    if (stages.has(SystemStage::PostUpdate))
        post_update_systems.push_back(&system);

    if (stages.has(SystemStage::Render))
        render_systems.push_back(&system);
}

void SystemManager::unregister_system(System *system, Flags<SystemStage> stages)
{
    if (stages.has(SystemStage::Physics))
        std::erase(physics_systems, system);

    if (stages.has(SystemStage::PreUpdate))
        std::erase(pre_update_systems, system);

    if (stages.has(SystemStage::Update))
        std::erase(update_systems, system);

    if (stages.has(SystemStage::PostUpdate))
        std::erase(post_update_systems, system);

    if (stages.has(SystemStage::Render))
        std::erase(render_systems, system);
}
