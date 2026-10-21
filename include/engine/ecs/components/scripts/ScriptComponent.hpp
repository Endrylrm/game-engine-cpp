#pragma once
#include <memory>
#include <vector>

#include "Script.hpp"

struct ScriptComponent
{
    std::vector<std::unique_ptr<Script>> scripts;
};