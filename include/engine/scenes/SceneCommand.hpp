#pragma once
#include "engine/core/string/StringHandle.hpp"

enum class SceneCommandType
{
    Load,
    LoadAdditive,
    Unload,
    UnloadAll
};

struct SceneCommand
{
    SceneCommandType type;
    StringHandle id;
};
