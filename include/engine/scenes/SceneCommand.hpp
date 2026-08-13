#pragma once
#include <engine/core/string/StringHandle.hpp>

#include "SceneId.hpp"

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
    SceneId id;
};
