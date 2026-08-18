#pragma once
#include <engine/core/string/StringHandle.hpp>

#include "SceneId.hpp"

enum class SceneCommandType
{
    Load,
    LoadAdditive,
    LoadPersistent,
    Unload,
    UnloadNonPersistent,
    UnloadAll
};

struct SceneCommand
{
    SceneCommandType type;
    SceneId id;
};
