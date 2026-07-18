#pragma once
#include "engine/scenes/SceneRegistry.hpp"

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
