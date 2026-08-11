#include "engine/ecs/registry/managers/SystemManager.hpp"

void SystemManager::init()
{
    for (auto &system : systems)
        system->onInit();
}

void SystemManager::physics(float fixedDeltaTime)
{
    for (auto *system : physicsSystems)
        system->onPhysics(fixedDeltaTime);
}

void SystemManager::preUpdate()
{
    for (auto *system : preUpdateSystems)
        system->onPreUpdate();
}

void SystemManager::update(float deltaTime)
{
    for (auto *system : updateSystems)
        system->onUpdate(deltaTime);
}

void SystemManager::postUpdate()
{
    for (auto *system : postUpdateSystems)
        system->onPostUpdate();
}

void SystemManager::render(Renderer &renderer)
{
    for (auto *system : renderSystems)
        system->onRender(renderer);
}

void SystemManager::unload()
{
    for (auto &system : systems)
        system->onUnload();

    systems.clear();
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
