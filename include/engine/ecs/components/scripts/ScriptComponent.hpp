#pragma once
#include <memory>
#include <vector>

#include <engine/ecs/components/scripts/Script.hpp>

struct ScriptComponent
{
    std::vector<std::unique_ptr<Script>> scripts;
};