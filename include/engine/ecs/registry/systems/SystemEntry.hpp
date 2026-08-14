#pragma once
#include <memory>

#include <engine/core/helpers/Flags.hpp>
#include <engine/ecs/registry/systems/SystemStage.hpp>
#include <engine/ecs/systems/System.hpp>

struct SystemEntry
{
    std::unique_ptr<System> system;
    Flags<SystemStage> stages;
};
