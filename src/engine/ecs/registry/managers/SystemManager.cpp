#include "engine/ecs/registry/managers/SystemManager.hpp"

#include "engine/ecs/world/World.hpp"

void SystemManager::init()
{
    for (auto &entry : systems)
        entry.system->onInit(world);
}

void SystemManager::physics(float fixedDeltaTime)
{
    for (auto *system : physicsSystems)
        system->onPhysics(world, fixedDeltaTime);
}

void SystemManager::preUpdate()
{
    for (auto *system : preUpdateSystems)
        system->onPreUpdate(world);
}

void SystemManager::update(float deltaTime)
{
    for (auto *system : updateSystems)
        system->onUpdate(world, deltaTime);
}

void SystemManager::postUpdate()
{
    for (auto *system : postUpdateSystems)
        system->onPostUpdate(world);
}

void SystemManager::render(Renderer &renderer)
{
    for (auto *system : renderSystems)
        system->onRender(world, renderer);
}

void SystemManager::unload()
{
    for (auto &entry : systems)
        entry.system->onUnload(world);

    systems.clear();
    physicsSystems.clear();
    preUpdateSystems.clear();
    updateSystems.clear();
    postUpdateSystems.clear();
    renderSystems.clear();
}

void SystemManager::registerSystem(System &system, Flags<SystemStage> stages)
{
    if (stages.has(SystemStage::Physics))
        physicsSystems.push_back(&system);

    if (stages.has(SystemStage::PreUpdate))
        preUpdateSystems.push_back(&system);

    if (stages.has(SystemStage::Update))
        updateSystems.push_back(&system);

    if (stages.has(SystemStage::PostUpdate))
        postUpdateSystems.push_back(&system);

    if (stages.has(SystemStage::Render))
        renderSystems.push_back(&system);
}

void SystemManager::unregisterSystem(System *system, Flags<SystemStage> stages)
{
    if (stages.has(SystemStage::Physics))
        std::erase(physicsSystems, system);

    if (stages.has(SystemStage::PreUpdate))
        std::erase(preUpdateSystems, system);

    if (stages.has(SystemStage::Update))
        std::erase(updateSystems, system);

    if (stages.has(SystemStage::PostUpdate))
        std::erase(postUpdateSystems, system);

    if (stages.has(SystemStage::Render))
        std::erase(renderSystems, system);
}
