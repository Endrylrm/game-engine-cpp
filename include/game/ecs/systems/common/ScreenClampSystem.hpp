#pragma once
#include <engine/ecs/registry/Registry.hpp>
#include <engine/ecs/systems/System.hpp>

class ScreenClampSystem : public System
{
public:
    explicit ScreenClampSystem(Registry &registry) : registry(registry) {}
    void onPostUpdate() override;

private:
    Registry &registry;
};
